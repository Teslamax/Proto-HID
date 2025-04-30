# Proto-HID VoiceMeeter Control Interface

**Documentation Date:** 2025-04-30  
**MCU:** SparkFun Qwiic Pro Micro (ATmega32U4, USB-C, 5V/16MHz)  
**Peripherals:**  
- 2x Adafruit Seesaw Rotary Encoders (I2C, 0x36 and 0x37)  
- Adafruit NeoKey 1x4 (I2C, 0x30)  
- SSD1306 OLED Display (I2C, rotated 90° CW)

---

## 🎯 Project Purpose

A USB-connected control interface for VoiceMeeter on Windows, allowing:

- Hardware volume/mute control of 3 input channels (VBAN/virtual/system)
- USB MIDI CC and HID control
- Visual status display via OLED
- Fallback behavior when host feedback is missing
- Integration path for ANAVI Knobs 3 and KSP Controller projects

---

## 🎚️ Channel Mapping

| Channel Name | VoiceMeeter Input | MIDI Control | Encoder/Button |
|--------------|-------------------|---------------|----------------|
| **Zuban**    | Hardware Input 1  | CC 1          | Encoder 3 (future) |
| **Tovan**    | Hardware Input 2  | CC 2          | Encoder 1       |
| **Haruna**   | Virtual Input     | CC 3          | Encoder 2       |

---

## 🌀 Control Behavior

- **Encoder Rotation** → MIDI CC (volume/gain)
- **Short Press** → Toggle Mute
- **Long Press** → Reset to 0 dB (volume)

---

## 🖥️ Host-Side Script

Implemented in **Python 3** on Windows using:

- `VoicemeeterRemote64.dll` (official API)
- `pyserial` to write to USB CDC

**Behavior:**

- Polls VoiceMeeter every 500ms
- Sends changes over serial in this format:
  ```
  TOVAN:MUTE=0 GAIN=-3.0
  ```

This keeps the microcontroller in sync with actual system state.

---

## 📺 OLED Display Details

### Orientation
- Mounted vertically with top on the left
- Uses:
  ```cpp
  display.setRotation(1);  // 90° clockwise
  ```

### Display Modes

| Mode | Trigger | Output |
|------|---------|--------|
| Live | Host status active | Shows mute/gain for all inputs |
| Fallback | No USB serial for >5s | Shows “⚠️ No Host Feedback” |
| Input-only | During local control | Displays “Sent MUTE” or “Set -4.0 dB” |
| Demo | CLI command | Shows simulated values for development |

---

## 📂 Code Layout

```
proto-hid/
├── proto-hid.ino
└── src/
    ├── config.h
    ├── cli_parser.cpp
    ├── cli_parser.h
    ├── input_manager.cpp
    ├── input_manager.h
    ├── midi_manager.cpp
    ├── midi_manager.h
    ├── display_manager.cpp  // (planned)
    └── display_manager.h    // (planned)
```

---

## ✅ Failsafe Strategy

- Local encoder/button actions update OLED even without PC
- Serial parser tracks last update time
- Auto switches between “connected” and “disconnected” views
- Fully self-contained if Windows-side script is not present

---

## 🛠️ Phase Breakdown

| Phase | Description |
|-------|-------------|
| **Phase 1** | Replace JC Pro with Pro Micro, test NeoKey + encoders |
| **Phase 2** | Connect to VoiceMeeter (Haruna) via MIDI, OLED active |
| **Phase 3** | Add Zuban, finalize assistant control |
| **Phase 4** | Expand HID subsystem, integrate with KSP Controller |

---

## 🚧 Next Tasks

- [ ] Build `display_manager` module
- [ ] Add MIDI mapping to `midi_manager`
- [ ] Add `/display demo` and `/oled on|off` CLI commands
- [ ] Finalize host-side Python monitor and auto-start
