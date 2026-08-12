"""Client and scenario input driver for melonDS's localhost control API."""
from __future__ import annotations

import json
import math
import pathlib
import socket
import time

from rsp import RspError


BUTTONS = {
    "button_a": "A",
    "button_b": "B",
    "button_x": "X",
    "button_y": "Y",
    "dpad_up": "Up",
    "dpad_down": "Down",
    "dpad_left": "Left",
    "dpad_right": "Right",
    "l": "L",
    "r": "R",
    "start": "Start",
    "select": "Select",
}


class ControlError(RuntimeError):
    pass


def _address(value):
    return int(value, 0) if isinstance(value, str) else int(value)


class MelonControl:
    def __init__(self, host="127.0.0.1", port=45987, token=None, timeout=30.0):
        self.host = host
        self.port = int(port)
        self.token = token
        self.timeout = float(timeout)
        self.next_id = 1

    def request(self, command, **parameters):
        request_id = self.next_id
        self.next_id += 1
        payload = {"id": request_id, "command": command, **parameters}
        if self.token:
            payload["token"] = self.token

        wire = json.dumps(payload, separators=(",", ":")).encode() + b"\n"
        with socket.create_connection((self.host, self.port), self.timeout) as sock:
            sock.settimeout(self.timeout)
            sock.sendall(wire)
            response_line = sock.makefile("rb").readline()
        if not response_line:
            raise ControlError("melonDS closed the control connection")
        response = json.loads(response_line)
        if response.get("id") != request_id:
            raise ControlError("melonDS returned a mismatched response ID")
        if not response.get("ok"):
            raise ControlError(response.get("error", "melonDS control request failed"))
        return response


class ControlBreakpointClient:
    """Expose protocol-2 managed breakpoints through cpp_probe's client API.

    ``cpp_probe`` originally spoke the GDB remote protocol directly.  Keeping
    the tiny adapter interface lets its capture and report code use melonDS's
    in-process breakpoint engine without maintaining a second implementation.
    Each protocol request uses a short-lived localhost socket, so there is no
    single-client session to wedge or detach.
    """

    def __init__(self, host="127.0.0.1", port=45987, timeout=2.0,
                 token=None, poll_interval=0.01):
        self.control = MelonControl(host, port, token, timeout)
        self.timeout = float(timeout)
        self.poll_interval = float(poll_interval)
        self._last_sequence = 0
        self._last_hit = None
        self._owned_breakpoints = set()

    @staticmethod
    def _hit(response):
        hit = response.get("last_breakpoint_hit") or None
        if not hit:
            return None
        return {
            **hit,
            "sequence": int(hit.get("sequence", 0)),
            "address": _address(hit["address"]),
        }

    def connect(self, retries=1, retry_delay=0.0):
        del retries, retry_delay
        try:
            ping = self.control.request("ping")
            if ping.get("protocol") != 2:
                raise RspError(
                    f"melonDS control protocol 2 required, got {ping.get('protocol')!r}")
            status = self.control.request("status")
        except (ControlError, OSError, ValueError) as exc:
            raise RspError(f"melonDS control connection failed: {exc}") from exc
        if not status.get("managed_breakpoints_available"):
            raise RspError("managed ARM9 breakpoints are unavailable; disable JIT")
        hit = self._hit(status)
        self._last_sequence = hit["sequence"] if hit else 0
        self._last_hit = hit
        return self

    def close(self):
        pass

    def set_breakpoint(self, addr, kind=4):
        # The in-process engine normalizes ARM/Thumb addresses itself.  Keep
        # accepting GDB's kind argument so cpp_probe needs no transport branch.
        del kind
        try:
            self.control.request("breakpoint_add", address=f"0x{addr:08x}")
        except (ControlError, OSError, ValueError) as exc:
            raise RspError(f"could not add managed breakpoint at {addr:#x}: {exc}") from exc
        self._owned_breakpoints.add(addr & ~1)
        return True

    def clear_breakpoint(self, addr, kind=4):
        del kind
        try:
            self.control.request("breakpoint_remove", address=f"0x{addr:08x}")
        except (ControlError, OSError, ValueError) as exc:
            raise RspError(f"could not remove managed breakpoint at {addr:#x}: {exc}") from exc
        self._owned_breakpoints.discard(addr & ~1)
        return True

    def read_mem(self, addr, length):
        try:
            response = self.control.request(
                "read_memory", address=f"0x{addr:08x}", size=int(length))
            return bytes.fromhex(response["data"])
        except (ControlError, OSError, KeyError, ValueError) as exc:
            raise RspError(f"could not read {length} byte(s) at {addr:#x}: {exc}") from exc

    def write_mem(self, addr, data):
        try:
            self.control.request(
                "write_memory", address=f"0x{addr:08x}", data=bytes(data).hex())
        except (ControlError, OSError, ValueError) as exc:
            raise RspError(f"could not write memory at {addr:#x}: {exc}") from exc
        return True

    def cont(self, expect_reply=False):
        del expect_reply
        try:
            status = self.control.request("status")
            hit = self._hit(status)
            if hit:
                self._last_sequence = max(self._last_sequence, hit["sequence"])
            self.control.request("resume")
        except (ControlError, OSError, ValueError) as exc:
            raise RspError(f"could not resume emulation: {exc}") from exc
        return ""

    def wait_for_stop(self):
        deadline = time.monotonic() + self.timeout
        while time.monotonic() < deadline:
            try:
                status = self.control.request("status")
            except (ControlError, OSError, ValueError) as exc:
                raise RspError(f"could not poll breakpoint status: {exc}") from exc
            hit = self._hit(status)
            if (status.get("state") == "breakpoint" and hit and
                    hit["sequence"] > self._last_sequence):
                try:
                    detail = self.control.request("breakpoint_list")
                except (ControlError, OSError, ValueError) as exc:
                    raise RspError(f"could not read breakpoint hit: {exc}") from exc
                self._last_hit = self._hit(detail)
                self._last_sequence = hit["sequence"]
                return "T05"
            time.sleep(self.poll_interval)
        raise TimeoutError("timed out waiting for a managed breakpoint")

    def read_registers(self):
        hit = self._last_hit
        if not hit or not hit.get("registers"):
            try:
                hit = self._hit(self.control.request("breakpoint_list"))
            except (ControlError, OSError, ValueError) as exc:
                raise RspError(f"could not read breakpoint registers: {exc}") from exc
        if not hit or not hit.get("registers"):
            raise RspError("no managed breakpoint register snapshot is available")
        raw_regs = hit["registers"]
        out = {f"r{i}": _address(raw_regs[f"r{i}"]) for i in range(16)}
        out["sp"], out["lr"], out["pc"] = out["r13"], out["r14"], out["r15"]
        out["cpsr"] = _address(raw_regs["cpsr"])
        out["cpsr_src"] = "control-api"
        out["words"] = [out[f"r{i}"] for i in range(16)] + [out["cpsr"]]
        out["raw"] = ""
        return out

    def research_snapshot(self):
        try:
            return self.control.request("research_snapshot")
        except (ControlError, OSError, ValueError) as exc:
            raise RspError(f"could not read research snapshot: {exc}") from exc

    def detach(self):
        # Match RSP detach's useful behavior: do not leave the emulator stopped.
        try:
            status = self.control.request("status")
            if status.get("state") == "breakpoint":
                self.control.request("resume")
        except (ControlError, OSError, ValueError):
            pass


class ControlMelonInput:
    """Driver-compatible deterministic DS input through the emulator thread."""

    def __init__(self, host="127.0.0.1", port=45987, token=None,
                 state_root=None, fps=59.8261, timeout=30.0):
        self.client = MelonControl(host, port, token, timeout)
        self.state_root = pathlib.Path(state_root).resolve() if state_root else None
        self.fps = float(fps)
        self.held = set()
        self._fractional_frames = 0.0
        self.client.request("ping")

    def focus(self):
        """Compatibility no-op: the socket backend never needs window focus."""
        self.client.request("ping")

    def resume(self):
        self.client.request("resume")

    def _buttons(self):
        try:
            return [BUTTONS[name] for name in sorted(self.held)]
        except KeyError as exc:
            raise ValueError(
                f"control API cannot synthesize emulator hotkey {exc.args[0]!r}; "
                "use a load_state action instead") from exc

    def _sync_input(self, touch=None):
        parameters = {"buttons": self._buttons()}
        if touch is not None:
            parameters["touch"] = touch
        self.client.request("set_input", **parameters)

    def key_down(self, control):
        if control not in BUTTONS:
            raise ValueError(
                f"control API cannot synthesize emulator hotkey {control!r}; "
                "use a load_state action instead")
        self.held.add(control)
        self._sync_input()

    def key_up(self, control):
        self.held.discard(control)
        self._sync_input()

    def release_all(self):
        self.held.clear()
        self.client.request("release_input")

    def close(self):
        self.held.clear()
        self.client.request("clear_input_override")

    def step_frames(self, frames):
        requested = int(frames)
        if requested < 0:
            raise ValueError("frame count cannot be negative")
        if requested == 0:
            return

        status = self.client.request("status")
        completed = int(status["completed_frames"])
        target = completed + requested
        while completed < target:
            chunk = min(target - completed, 600)
            try:
                response = self.client.request("step", frames=chunk)
                completed = int(response["completed_frames"])
            except ControlError as exc:
                if "managed breakpoint hit before frame step completed" not in str(exc):
                    raise
                # The collector needs the CPU stopped long enough to capture
                # registers and object memory.  Wait until it resumes the hit,
                # then finish the exact frame budget from the monotonic counter.
                while True:
                    status = self.client.request("status")
                    completed = int(status["completed_frames"])
                    if status.get("state") != "breakpoint":
                        break
                    time.sleep(0.005)

    def sleep(self, seconds):
        exact = self._fractional_frames + max(0.0, float(seconds)) * self.fps
        frames = math.floor(exact + 1e-9)
        self._fractional_frames = exact - frames
        self.step_frames(frames)

    def touch(self, x, y, seconds=0.08):
        x = float(x)
        y = float(y)
        if not 0.0 <= x <= 1.0 or not 0.0 <= y <= 1.0:
            raise ValueError("touch x/y must be normalized DS touch-screen coordinates")
        touch = {"x": round(x * 255), "y": round(y * 191)}
        self._sync_input(touch=touch)
        try:
            self.sleep(seconds)
        finally:
            self._sync_input()

    def load_state(self, path):
        path = pathlib.Path(path)
        if not path.is_absolute():
            path = (self.state_root or pathlib.Path.cwd()) / path
        path = path.resolve()
        if not path.is_file():
            raise FileNotFoundError(f"savestate not found: {path}")
        self.client.request("load_state", path=str(path))
