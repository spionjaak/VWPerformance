#include "OBD.h"

#include "VehicleData.h"

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEClient.h>
#include <BLERemoteCharacteristic.h>

//==================================================
// BLE CONFIG
//==================================================

BLEAddress obdAddress("a7:ef:58:e5:ae:96");

static BLEUUID serviceUUID("0000FFF0-0000-1000-8000-00805F9B34FB");
static BLEUUID rxUUID("0000FFF1-0000-1000-8000-00805F9B34FB");
static BLEUUID txUUID("0000FFF2-0000-1000-8000-00805F9B34FB");

static BLERemoteCharacteristic* pRX = nullptr;
static BLERemoteCharacteristic* pTX = nullptr;

static bool connected = false;

static unsigned long lastRPMRequest = 0;
static unsigned long lastTempRequest = 0;
static unsigned long lastBatteryRequest = 0;

//==================================================
// CALLBACK
//==================================================

void notifyCallback(
    BLERemoteCharacteristic* characteristic,
    uint8_t* data,
    size_t length,
    bool isNotify)
{
    String response = "";

    for(size_t i=0;i<length;i++)
        response += (char)data[i];

    String hexOnly = "";

    for(size_t i=0;i<response.length();i++)
    {
        if(isxdigit(response[i]))
            hexOnly += response[i];
    }

    //---------------- RPM ----------------

    int rpmIdx = hexOnly.indexOf("410C");

    if(rpmIdx != -1 && hexOnly.length() >= rpmIdx + 8)
    {
        int A = strtol(
            hexOnly.substring(rpmIdx+4,rpmIdx+6).c_str(),
            NULL,
            16);

        int B = strtol(
            hexOnly.substring(rpmIdx+6,rpmIdx+8).c_str(),
            NULL,
            16);

        vehicle.rpm = ((A*256)+B)/4;
        vehicle.rpmValid = true;
    }

    //---------------- TEMP ----------------

    int tempIdx = hexOnly.indexOf("4105");

    if(tempIdx != -1 && hexOnly.length() >= tempIdx + 6)
    {
        vehicle.coolantTemp =
            strtol(
                hexOnly.substring(tempIdx+4,tempIdx+6).c_str(),
                NULL,
                16
            ) - 40;

        vehicle.tempValid = true;
    }

    //---------------- BATTERY ----------------

    if(response.indexOf("V") != -1)
    {
        vehicle.batteryVoltage = response.toFloat();
        vehicle.batteryValid = true;
    }
}

//==================================================
// INIT
//==================================================

bool OBD_Init()
{
    BLEDevice::init("");

    BLEClient* client =
        BLEDevice::createClient();

    if(!client->connect(obdAddress))
        return false;

    BLERemoteService* service =
        client->getService(serviceUUID);

    if(service == nullptr)
        return false;

    pRX = service->getCharacteristic(rxUUID);
    pTX = service->getCharacteristic(txUUID);

    if(pRX == nullptr || pTX == nullptr)
        return false;

    pRX->registerForNotify(notifyCallback);

    delay(500);

    uint8_t ati[] =
    {
        0x41,0x54,0x49,0x0D
    };

    pTX->writeValue(ati,sizeof(ati),true);

    delay(500);

    uint8_t ate0[] =
    {
        0x41,0x54,0x45,0x30,0x0D
    };

    pTX->writeValue(ate0,sizeof(ate0),true);

    delay(500);

    uint8_t atsp0[] =
    {
        0x41,0x54,0x53,0x50,0x30,0x0D
    };

    pTX->writeValue(atsp0,sizeof(atsp0),true);

    connected = true;
    vehicle.obdConnected = true;

    return true;
}

//==================================================
// UPDATE
//==================================================

void OBD_Update()
{
    if(!connected)
        return;

    unsigned long now = millis();

    //==============================
    // RPM (80 ms)
    //==============================

    if(now - lastRPMRequest >= 80)
    {
        uint8_t cmd[] =
        {
            0x30,0x31,0x30,0x43,0x0D
        };

        pTX->writeValue(cmd,sizeof(cmd),true);

        lastRPMRequest = now;
    }

    //==============================
    // Coolant Temp (2 s)
    //==============================

    if(now - lastTempRequest >= 2000)
    {
        uint8_t cmd[] =
        {
            0x30,0x31,0x30,0x35,0x0D
        };

        pTX->writeValue(cmd,sizeof(cmd),true);

        lastTempRequest = now;
    }

    //==============================
    // Battery (5 s)
    //==============================

    if(now - lastBatteryRequest >= 5000)
    {
        uint8_t cmd[] =
        {
            0x41,0x54,0x52,0x56,0x0D
        };

        pTX->writeValue(cmd,sizeof(cmd),true);

        lastBatteryRequest = now;
    }
}

//==================================================
// STATUS
//==================================================

bool OBD_IsConnected()
{
    return connected;
}