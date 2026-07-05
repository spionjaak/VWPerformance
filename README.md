# VW Performance

A custom ESP32-based performance display for Volkswagen vehicles using BLE OBD-II.


## Development Status

Current Version

V1.0.1


## Features

- BLE connection to ELM327
- Real-time RPM
- Coolant temperature
- Battery voltage
- TFT ILI9341 display
- Modular architecture
- Startup screen
- Connection status

## Hardware

- ESP32 Dev Module
- ILI9341 TFT 320x240
- BLE ELM327 OBD-II Adapter

## Project Structure

```
VWPerformance/
│
├── Config.h
├── Display.cpp
├── Display.h
├── OBD.cpp
├── OBD.h
├── Screens.cpp
├── Screens.h
├── Startup.cpp
├── Startup.h
├── VehicleData.cpp
├── VehicleData.h
└── VWPerformance.ino
```

## Current Version

**V1.0.0**

### Implemented

- BLE OBD connection
- Engine RPM
- Coolant Temperature
- Battery Voltage
- Startup Screen
- Performance Dashboard

## Planned Features

- Vehicle Speed
- Boost Pressure
- Intake Air Temperature
- Oil Temperature
- Multi Screen UI
- Touch Navigation
- Settings Menu
- Automatic Reconnect
- Custom Themes
- Brightness Control
- Shift Light
- Performance Timer
- 0-100 km/h Timer
- Diagnostic Trouble Codes

## License

MIT License

---

Developed by Matej Spionjak