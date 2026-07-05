#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

extern Adafruit_ILI9341 tft;

//=============================
// INITIALIZATION
//=============================

void Display_Init();

void Display_Clear();

//=============================
// STARTUP
//=============================

void Display_ShowLogo();

void Display_ShowConnecting();

void Display_ShowConnected();

void Display_ShowMessage(const char* message);

//=============================
// PERFORMANCE SCREEN
//=============================

void Display_DrawPerformanceScreen();

void Display_UpdateRPM();

void Display_UpdateTemperature();

void Display_UpdateBattery();

void Display_UpdateAll();

#endif