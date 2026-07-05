#ifndef VEHICLEDATA_H
#define VEHICLEDATA_H

#include <stdint.h>

struct VehicleData
{
    // Engine
    uint16_t rpm = 0;
    uint8_t coolantTemp = 0;
    float batteryVoltage = 0.0f;

    // Vehicle
    uint8_t speed = 0;

    // Turbo
    float boost = 0.0f;

    // Status
    bool obdConnected = false;

    bool rpmValid = false;
    bool tempValid = false;
    bool batteryValid = false;
    bool speedValid = false;
    bool boostValid = false;
};

extern VehicleData vehicle;

#endif