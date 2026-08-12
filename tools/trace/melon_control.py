"""Client and scenario input driver for melonDS's localhost control API."""
from __future__ import annotations

import json
import math
import pathlib
import socket


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
        remaining = int(frames)
        if remaining < 0:
            raise ValueError("frame count cannot be negative")
        while remaining:
            chunk = min(remaining, 600)
            self.client.request("step", frames=chunk)
            remaining -= chunk

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
