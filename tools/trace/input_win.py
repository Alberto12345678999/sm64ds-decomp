"""Windows input actuator for deterministic melonDS trace scenarios.

This module deliberately drives melonDS through its configured keyboard
surface instead of writing NDS keypad MMIO through GDB.  melonDS refreshes the
hardware key register continuously, so a debugger write there is not a stable
input source.  The scenario runner owns the one GDB session while this actuator
uses normal Win32 keyboard events.

The default bindings are read from ``melonDS.toml``.  Only the small subset of
Qt key values emitted by melonDS 1.1's keyboard mapper is decoded; unsupported
or unbound controls fail loudly instead of silently pressing a different key.
"""
from __future__ import annotations

import ctypes
from ctypes import wintypes
import pathlib
import sys
import time

try:
    import tomllib
except ImportError:  # pragma: no cover - Python 3.11+ is used by the repo
    tomllib = None


DS_TO_CONFIG = {
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

# Qt::Key values written by melonDS 1.1 -> Win32 virtual-key values.
_QT_TO_VK = {
    0x01000000: 0x1B,  # Escape
    0x01000003: 0x08,  # Backspace
    0x01000004: 0x0D,  # Return
    0x01000005: 0x0D,  # Keypad Enter
    0x01000012: 0x25,  # Left
    0x01000013: 0x26,  # Up
    0x01000014: 0x27,  # Right
    0x01000015: 0x28,  # Down
}
for _n in range(1, 25):
    _QT_TO_VK[0x0100002F + _n] = 0x6F + _n  # F1..F24

_EXTENDED_VKS = {0x25, 0x26, 0x27, 0x28}
_KEYEVENTF_EXTENDEDKEY = 0x0001
_KEYEVENTF_KEYUP = 0x0002
_MOUSEEVENTF_LEFTDOWN = 0x0002
_MOUSEEVENTF_LEFTUP = 0x0004
_INPUT_MOUSE = 0
_INPUT_KEYBOARD = 1
_SW_RESTORE = 9


def qt_key_to_vk(value: int) -> int:
    """Translate one melonDS/Qt keyboard binding to a Win32 virtual key."""
    if value in _QT_TO_VK:
        return _QT_TO_VK[value]
    if 0x20 <= value <= 0x7E:
        return ord(chr(value).upper())
    raise ValueError(f"unsupported melonDS Qt key value {value:#x}")


def default_config_path() -> pathlib.Path:
    candidates = [
        pathlib.Path.home() / "melonDS" / "melonDS.toml",
        pathlib.Path.cwd() / "melonDS.toml",
    ]
    for path in candidates:
        if path.is_file():
            return path
    raise FileNotFoundError(
        "melonDS.toml not found; pass --melon-config with its full path")


def load_bindings(path: str | pathlib.Path | None = None) -> dict[str, int]:
    """Load canonical DS-control -> Win32 virtual-key bindings."""
    if tomllib is None:
        raise RuntimeError("Python tomllib is required to read melonDS.toml")
    path = pathlib.Path(path) if path else default_config_path()
    data = tomllib.loads(path.read_text(encoding="utf-8"))
    try:
        configured = data["Instance0"]["Keyboard"]
    except KeyError as exc:
        raise ValueError(f"{path} has no [Instance0.Keyboard] table") from exc

    out = {}
    for control, config_name in DS_TO_CONFIG.items():
        value = configured.get(config_name, -1)
        if isinstance(value, int) and value >= 0:
            out[control] = qt_key_to_vk(value)
    # melonDS's default quick-load hotkeys.  They are named as raw hotkeys so
    # scenarios do not pretend they came from the DS keypad mapping above.
    for slot in range(1, 9):
        out[f"hotkey_load_slot_{slot}"] = 0x6F + slot  # F1..F8
    return out


if sys.platform == "win32":
    _ULONG_PTR = wintypes.WPARAM

    class _KEYBDINPUT(ctypes.Structure):
        _fields_ = [
            ("wVk", wintypes.WORD),
            ("wScan", wintypes.WORD),
            ("dwFlags", wintypes.DWORD),
            ("time", wintypes.DWORD),
            ("dwExtraInfo", _ULONG_PTR),
        ]

    class _MOUSEINPUT(ctypes.Structure):
        # INPUT's union must include its largest member even when we only send
        # keyboard events.  Omitting MOUSEINPUT shrinks sizeof(INPUT) from the
        # Win64 ABI's 40 bytes to 32 and SendInput fails with ERROR_INVALID_PARAMETER.
        _fields_ = [
            ("dx", wintypes.LONG),
            ("dy", wintypes.LONG),
            ("mouseData", wintypes.DWORD),
            ("dwFlags", wintypes.DWORD),
            ("time", wintypes.DWORD),
            ("dwExtraInfo", _ULONG_PTR),
        ]

    class _HARDWAREINPUT(ctypes.Structure):
        _fields_ = [
            ("uMsg", wintypes.DWORD),
            ("wParamL", wintypes.WORD),
            ("wParamH", wintypes.WORD),
        ]

    class _INPUTUNION(ctypes.Union):
        _fields_ = [
            ("mi", _MOUSEINPUT),
            ("ki", _KEYBDINPUT),
            ("hi", _HARDWAREINPUT),
        ]

    class _INPUT(ctypes.Structure):
        _anonymous_ = ("u",)
        _fields_ = [("type", wintypes.DWORD), ("u", _INPUTUNION)]


class Win32MelonInput:
    """Send configured DS controls to the visible melonDS window."""

    def __init__(self, bindings=None, config_path=None, title_contains="melonDS"):
        if sys.platform != "win32":
            raise RuntimeError("the melonDS keyboard actuator currently requires Windows")
        self.bindings = dict(bindings or load_bindings(config_path))
        self.title_contains = title_contains.lower()
        self.hwnd = self._find_window()
        self.held = set()

    def _find_window(self):
        user32 = ctypes.windll.user32
        found = []
        callback_type = ctypes.WINFUNCTYPE(wintypes.BOOL, wintypes.HWND, wintypes.LPARAM)

        @callback_type
        def visit(hwnd, _):
            if not user32.IsWindowVisible(hwnd):
                return True
            length = user32.GetWindowTextLengthW(hwnd)
            if not length:
                return True
            buf = ctypes.create_unicode_buffer(length + 1)
            user32.GetWindowTextW(hwnd, buf, len(buf))
            if self.title_contains in buf.value.lower():
                found.append(hwnd)
                return False
            return True

        user32.EnumWindows(visit, 0)
        if not found:
            raise RuntimeError(f"no visible window containing {self.title_contains!r}")
        return found[0]

    def focus(self):
        user32 = ctypes.windll.user32
        user32.ShowWindow(self.hwnd, _SW_RESTORE)
        if not user32.SetForegroundWindow(self.hwnd):
            raise RuntimeError(
                "Windows refused to focus melonDS; click its window once and retry")
        time.sleep(0.1)

    @staticmethod
    def _send_vk(vk, key_up=False):
        flags = _KEYEVENTF_KEYUP if key_up else 0
        if vk in _EXTENDED_VKS:
            flags |= _KEYEVENTF_EXTENDEDKEY
        event = _INPUT(type=_INPUT_KEYBOARD,
                       ki=_KEYBDINPUT(vk, 0, flags, 0, 0))
        sent = ctypes.windll.user32.SendInput(1, ctypes.byref(event), ctypes.sizeof(event))
        if sent != 1:
            raise ctypes.WinError()

    def key_down(self, control):
        if control not in self.bindings:
            raise ValueError(f"melonDS control {control!r} is unbound or unsupported")
        if control not in self.held:
            self._send_vk(self.bindings[control])
            self.held.add(control)

    def key_up(self, control):
        if control in self.held:
            self._send_vk(self.bindings[control], key_up=True)
            self.held.remove(control)

    def release_all(self):
        for control in list(self.held):
            self.key_up(control)

    @staticmethod
    def _send_mouse(flags):
        event = _INPUT(type=_INPUT_MOUSE,
                       mi=_MOUSEINPUT(0, 0, 0, flags, 0, 0))
        sent = ctypes.windll.user32.SendInput(
            1, ctypes.byref(event), ctypes.sizeof(event))
        if sent != 1:
            raise ctypes.WinError()

    def touch(self, x, y, seconds=0.08):
        """Click a normalized point in the melonDS client area."""
        x = float(x)
        y = float(y)
        if not 0.0 <= x <= 1.0 or not 0.0 <= y <= 1.0:
            raise ValueError("touch x/y must be normalized values from 0 to 1")
        user32 = ctypes.windll.user32
        rect = wintypes.RECT()
        if not user32.GetClientRect(self.hwnd, ctypes.byref(rect)):
            raise ctypes.WinError()
        width = rect.right - rect.left
        height = rect.bottom - rect.top
        if width <= 1 or height <= 1:
            raise RuntimeError("melonDS client area is too small for touch input")
        point = wintypes.POINT(
            round((width - 1) * x), round((height - 1) * y))
        if not user32.ClientToScreen(self.hwnd, ctypes.byref(point)):
            raise ctypes.WinError()
        if not user32.SetCursorPos(point.x, point.y):
            raise ctypes.WinError()
        self._send_mouse(_MOUSEEVENTF_LEFTDOWN)
        time.sleep(max(0.0, float(seconds)))
        self._send_mouse(_MOUSEEVENTF_LEFTUP)


def _controls(step):
    value = step.get("keys", step.get("key"))
    if isinstance(value, str):
        return [value]
    if isinstance(value, list) and all(isinstance(v, str) for v in value):
        return value
    raise ValueError(f"step requires key/keys: {step!r}")


def _sleep_interruptibly(seconds, sleep, should_stop):
    deadline = time.monotonic() + max(0.0, float(seconds))
    while not should_stop():
        remaining = deadline - time.monotonic()
        if remaining <= 0:
            return
        sleep(min(0.05, remaining))


def run_steps(driver, steps, sleep=time.sleep, should_stop=lambda: False,
              announce=print):
    """Execute validated scenario steps against a driver-like object."""
    try:
        for index, step in enumerate(steps, 1):
            if should_stop():
                break
            action = step.get("action")
            note = step.get("note")
            if note:
                announce(f"[*] input step {index}: {note}")
            if action == "focus":
                driver.focus()
            elif action == "wait":
                _sleep_interruptibly(step.get("seconds", 0), sleep, should_stop)
            elif action == "touch":
                driver.touch(step.get("x"), step.get("y"),
                             step.get("seconds", 0.08))
            elif action in ("tap", "hold"):
                controls = _controls(step)
                for control in controls:
                    driver.key_down(control)
                try:
                    seconds = step.get("seconds", 0.08 if action == "tap" else None)
                    if seconds is None:
                        raise ValueError(f"hold step requires seconds: {step!r}")
                    _sleep_interruptibly(seconds, sleep, should_stop)
                finally:
                    for control in reversed(controls):
                        driver.key_up(control)
            else:
                raise ValueError(f"unsupported input action {action!r} in step {index}")
    finally:
        driver.release_all()
