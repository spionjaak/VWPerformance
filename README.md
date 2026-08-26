# VW Performance

A custom ESP32-based performance display for Volkswagen vehicles using BLE OBD-II.

The project connects to a BLE ELM327 OBD-II adapter and displays real-time vehicle data on an ILI9341 TFT display.

---

## Features

- BLE connection to ELM327
- Real-time engine RPM
- Coolant temperature monitoring
- Battery voltage monitoring
- ILI9341 TFT display
- Performance dashboard
- Custom startup screen
- Connection status screens
- Connected and error status icons
- Temperature and battery icons
- Adaptive RPM response
- RPM deadband for stable idle readings
- Reduced display flickering
- RPM test mode for testing without an OBD connection
- Modular architecture

---

## Hardware

- ESP32 Dev Module
- ILI9341 TFT Display (320x240)
- BLE ELM327 OBD-II Adapter

---

## Displayed Vehicle Data

| Data | OBD Command |
|---|---|
| Engine RPM | `010C` |
| Coolant Temperature | `0105` |
| Battery Voltage | `ATRV` |

---

## Project Structure

```text
VWPerformance/
|
|-- Config.h
|-- Display.cpp
|-- Display.h
|-- Logos.cpp
|-- Logos.h
|-- OBD.cpp
|-- OBD.h
|-- Screens.cpp
|-- Screens.h
|-- Startup.cpp
|-- Startup.h
|-- VehicleData.cpp
|-- VehicleData.h
|-- VWPerformance.ino
|
|-- CHANGELOG.md
`-- README.md
```

---

## Current Version

**v1.0.3**

### v1.0.3 Highlights

- Improved startup and connection screens
- Added custom bitmap icons
- Redesigned temperature and battery information section
- Improved RPM responsiveness
- Added adaptive RPM smoothing
- Added RPM deadband to reduce small idle fluctuations
- Reduced display flickering
- Added RPM test mode for development without an OBD connection

---

## Planned Features

### Vehicle Data

- Vehicle Speed
- Boost Pressure
- Intake Air Temperature
- Oil Temperature

### Interface

- Multi Screen UI
- Touch Navigation
- Settings Menu
- Custom Themes
- Brightness Control

### Performance

- Shift Light
- Performance Timer
- 0-100 km/h Timer

### OBD

- Automatic Reconnect
- Diagnostic Trouble Codes


---

Developed by Matej Spionjak
