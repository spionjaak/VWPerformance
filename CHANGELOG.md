# VW Performance
# Changelog

All notable changes to this project will be documented here.

## 1.0.3 

### Added
- Added bitmap icons for coolant temperature and battery voltage
- Added RPM test mode for testing the display without an OBD connection

### Changed
- Redesigned the lower information section
- Improved RPM display responsiveness with adaptive smoothing
- Added RPM deadband to reduce small fluctuations at idle
- Improved display refresh behavior
- Updated startup and connection screens

### Fixed
- Reduced RPM display flickering
- Reduced unnecessary temperature and battery display redraws

## 1.0.2

### Added
- Boot screen
- Connecting screen
- Connected screen
- Error screen
- Bitmap icon support

### Changed
- Redesigned startup UI
- Refactored startup rendering
- Improved display layout

---

## V1.0.1

### Added

- Redesigned performance screen
- Centered RPM display
- Improved RPM bar layout
- Cleaner temperature and battery section

### Improved

- Optimized OBD polling scheduler
- Independent polling intervals for RPM, coolant temperature and battery voltage
- Significantly smoother RPM updates
- Improved overall UI readability

---

## V1.0.0

### Initial Release

- BLE OBD communication
- RPM monitoring
- Coolant temperature
- Battery voltage
- Startup screen
- Performance screen
