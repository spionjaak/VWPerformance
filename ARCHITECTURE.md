# ARCHITECTURE.md

# VW Performance Display -- Architecture

## Vision

The goal of this project is to build a professional ESP32-based
automotive performance display with a modular architecture that can grow
from a student prototype into a real product.

------------------------------------------------------------------------

## Folder Structure

``` text
VWPerformance/
├── VWPerformance.ino
├── Config/
├── Core/
├── Display/
├── Widgets/
├── Screens/
├── Assets/
├── Utils/
├── README.md
├── CHANGELOG.md
└── ARCHITECTURE.md
```

## Layers

### Config

Pins, constants and feature flags.

### Core

-   OBD
-   VehicleData

Never draws anything.

### Display

Low level TFT driver.

### Widgets

Reusable UI components: - Header - RPM Bar - RPM Value - Bottom Bar -
Battery - Temperature - Speed - Status

### Screens

Composed from widgets: - Startup - Performance - Speed - Diagnostics -
Settings

## Data Flow

``` text
OBD -> VehicleData -> Screen -> Widgets -> Display -> TFT
```

## Theme System

Future: - Theme.primary - Theme.warning - Theme.danger - Theme.text -
Theme.background

## Roadmap

### V1.0

-   BLE
-   RPM
-   Temperature
-   Battery

### V1.1

-   Widget architecture
-   New UI

### V1.2

-   Touch
-   Swipe
-   Screen manager

### V1.3

-   SD Assets
-   Themes

### V2.0

-   PCB
-   Enclosure
-   OTA

## Coding Rules

1.  One file = one responsibility.
2.  OBD never draws UI.
3.  Widgets are reusable.
4.  Screens contain widgets.
5.  Commit every completed feature.

Developed by Matej Spionjak
