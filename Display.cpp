#include "Display.h"
#include "Logos.h"
#include "Config.h"
#include "VehicleData.h"

static uint16_t rpmColor = COLOR_GREEN;

static float displayedRPM = 0;

static int stableRPM = 0;

static int lastRPM = -1;
static int lastRPMX = 0;
static uint16_t lastRPMWidth = 0;

Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

//====================================
// PRIVATE FUNCTIONS
//====================================


static void updateDisplayedRPM()
{
    // Ako se RPM promijenio više od 10,
    // postavi novi cilj
    if(abs(vehicle.rpm - stableRPM) >= 10)
    {
        stableRPM = vehicle.rpm;
    }

    float difference =
        stableRPM - displayedRPM;

    float absoluteDifference =
        abs(difference);

    // Gotovo ista vrijednost
    if(absoluteDifference < 5)
    {
        displayedRPM = stableRPM;
        return;
    }

    float speed;

    // Velika promjena - brzo reagiraj
    if(absoluteDifference > 1500)
    {
        speed = 0.70f;
    }

    // Srednja promjena
    else if(absoluteDifference > 500)
    {
        speed = 0.50f;
    }

    // Manja promjena
    else if(absoluteDifference > 150)
    {
        speed = 0.35f;
    }

    // Sitna promjena
    else
    {
        speed = 0.20f;
    }

    displayedRPM += difference * speed;
}

static void drawHeader()
{
    // Clear header area
    tft.fillRect(
        0,
        0,
        SCREEN_WIDTH,
        40,
        COLOR_BACKGROUND
    );

    tft.setTextSize(2);
    tft.setTextColor(COLOR_TEXT);

    const char* title = "VW PERFORMANCE";

    int16_t x1;
    int16_t y1;

    uint16_t w;
    uint16_t h;

    tft.getTextBounds(
        title,
        0,
        0,
        &x1,
        &y1,
        &w,
        &h
    );

    int x =
        (SCREEN_WIDTH - w) / 2;

    tft.setCursor(
        x,
        12
    );

    tft.print(title);

    tft.drawFastHLine(
        10,
        38,
        SCREEN_WIDTH - 20,
        COLOR_RED
    );
}

static void drawRPMBar()
{
    const int startX = 20;
    const int startY = 55;

    const int segments = 20;

    const int segmentWidth = 12;
    const int segmentHeight = 18;

    const int gap = 2;

    int activeSegments = map(
        (int)displayedRPM,
        0,
        MAX_RPM,
        0,
        segments
    );

    for(int i = 0; i < segments; i++)
    {
        uint16_t color = ILI9341_DARKGREY;

        if(i < activeSegments)
        {
            if(i < 12)
                color = COLOR_GREEN;
            else if(i < 16)
                color = COLOR_YELLOW;
            else
                color = COLOR_RED;
        }

        int x = startX + i * (segmentWidth + gap);

        tft.fillRoundRect(
            x,
            startY,
            segmentWidth,
            segmentHeight,
            2,
            color
        );
    }
}

static void drawRPMText()
{
    int currentRPM = (int)displayedRPM;

    
    if(currentRPM == lastRPM)
        return;

    
    if(lastRPM != -1)
    {
        tft.fillRect(
            lastRPMX,
            90,
            lastRPMWidth,
            50,
            COLOR_BACKGROUND
        );
    }

    // Novi RPM tekst
    String rpmString = String(currentRPM);

    int16_t x1, y1;
    uint16_t w, h;

    tft.setTextSize(6);

    tft.getTextBounds(
        rpmString,
        0,
        0,
        &x1,
        &y1,
        &w,
        &h
    );

    int rpmX = (SCREEN_WIDTH - w) / 2;

    // Nacrtaj novi RPM
    tft.setCursor(rpmX, 90);
    tft.setTextColor(rpmColor);
    tft.print(rpmString);

    // Spremi podatke za sljedeći put
    lastRPM = currentRPM;
    lastRPMX = rpmX;
    lastRPMWidth = w;
}

static void drawInfo()
{
    // Očisti donji dio
    tft.fillRect(
        0,
        170,
        SCREEN_WIDTH,
        70,
        COLOR_BACKGROUND
    );

    // Gornja separator linija
    tft.drawFastHLine(
        10,
        170,
        SCREEN_WIDTH - 20,
        ILI9341_DARKGREY
    );

    // ==================================
    // TEMPERATURE
    // ==================================

    tft.drawBitmap(
        25,
        190,
        tempIcon,
        32,
        32,
        COLOR_INFO
    );

    tft.setTextSize(3);
    tft.setTextColor(COLOR_TEXT);

    if(vehicle.tempValid)
    {
        tft.setCursor(65, 198);
        tft.print(vehicle.coolantTemp);
        tft.print((char)247);
        tft.print("C");
    }
    else
    {
        tft.setCursor(65, 198);
        tft.print("--");
    }

    // ==================================
    // BATTERY
    // ==================================

    tft.drawBitmap(
        180,
        190,
        batteryIcon,
        32,
        32,
        COLOR_INFO
    );

    tft.setTextSize(3);
    tft.setTextColor(COLOR_TEXT);

    if(vehicle.batteryValid)
    {
        tft.setCursor(220, 198);
        tft.print(vehicle.batteryVoltage, 1);
        tft.print("V");
    }
    else
    {
        tft.setCursor(220, 198);
        tft.print("--.-");
    }
}

static void drawLoadingDots(uint8_t activeDot)
{
    const int centerX = SCREEN_WIDTH / 2;
    const int y = 212;

    const int spacing = 18;
    const int radius = 4;

    for(int i = 0; i < 3; i++)
    {
        int x = centerX - spacing + i * spacing;

        if(i == activeDot)
        {
            tft.fillCircle(
                x,
                y,
                radius,
                COLOR_TEXT
            );
        }
        else
        {
            tft.drawCircle(
                x,
                y,
                radius,
                ILI9341_DARKGREY
            );
        }
    }
}

static void drawLogo()
{
    int16_t x1, y1;
    uint16_t w, h;

    tft.setTextColor(COLOR_TEXT);
    tft.setTextSize(5);

    const char* vw = "VW";

    tft.getTextBounds(vw, 0, 0, &x1, &y1, &w, &h);
    tft.setCursor((SCREEN_WIDTH - w) / 2, 55);
    tft.print(vw);

    tft.setTextSize(2);

    const char* title = "VW PERFORMANCE";

    tft.getTextBounds(title, 0, 0, &x1, &y1, &w, &h);
    tft.setCursor((SCREEN_WIDTH - w) / 2, 120);
    tft.print(title);
}

static void drawCheckMark()
{
   tft.drawBitmap(
    140,
    160,
    checkMark,
    32,
    32,
    COLOR_GREEN
);
}

static void drawWarningMark()
{
 tft.drawBitmap(
        144,
        145,
        warningMark,
        32,
        32,
        COLOR_RED
    );
}
//====================================
// PUBLIC FUNCTIONS
//====================================

void Display_Init()
{
    tft.begin();

    tft.setRotation(1);

    tft.fillScreen(COLOR_BACKGROUND);
}

void Display_Clear()
{
    tft.fillScreen(COLOR_BACKGROUND);
}

void Display_ShowLogo()
{
    Display_Clear();

    drawLogo();

    int16_t x1, y1;
    uint16_t w, h;

    tft.setTextColor(COLOR_DARKGREY);
    tft.setTextSize(2);

    tft.getTextBounds(FW_VERSION, 0, 0, &x1, &y1, &w, &h);

    tft.setCursor((SCREEN_WIDTH - w) / 2, 195);

    tft.print(FW_VERSION);
}

void Display_ShowConnecting()
{
    Display_Clear();
    drawLogo();

    tft.setTextSize(2);
    tft.setTextColor(COLOR_TEXT);

    const char* text = "Connecting";

    int16_t x1, y1;
    uint16_t w, h;

    tft.getTextBounds(
        text,
        0,
        0,
        &x1,
        &y1,
        &w,
        &h
    );

    tft.setCursor(
        (SCREEN_WIDTH - w) / 2,
        182
    );

    tft.print(text);

    drawLoadingDots(0);
}

void Display_UpdateConnecting()
{
    static uint8_t dot = 0;
    static unsigned long lastUpdate = 0;

    if(millis() - lastUpdate < 250)
        return;

    lastUpdate = millis();

    drawLoadingDots(dot);

    dot++;

    if(dot >= 3)
        dot = 0;
}

void Display_ShowConnected()
{
    Display_Clear();

    drawLogo();

    drawCheckMark();

    tft.setTextSize(2);
    tft.setTextColor(COLOR_GREEN);

    const char* text = "Connected";

    int16_t x1, y1;
    uint16_t w, h;

    tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

    tft.setCursor((SCREEN_WIDTH - w) / 2, 200);
    tft.print(text);
}

void Display_ShowError()
{
    Display_Clear();

    drawLogo();
    drawWarningMark();

    tft.setTextSize(2);
    tft.setTextColor(COLOR_RED);

    const char* text = "Connection Failed";

    int16_t x1, y1;
    uint16_t w, h;

    tft.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

    tft.setCursor((SCREEN_WIDTH - w) / 2, 190);
    tft.print(text);

    tft.setTextSize(1);
    tft.setTextColor(COLOR_LIGHTGREY);

    const char* text2 = "Check OBD Adapter";

    tft.getTextBounds(text2, 0, 0, &x1, &y1, &w, &h);
    tft.setCursor((SCREEN_WIDTH - w) / 2, 215);
    tft.print(text2);
}

void Display_ShowMessage(const char* message,uint16_t color)
{
   tft.fillRect(
        0,
        170,
        SCREEN_WIDTH,
        70,
        COLOR_BACKGROUND
    );




    tft.setTextSize(2);
    tft.setTextColor(color);

    tft.setCursor(50,190);
    tft.print(message);
}

void Display_DrawPerformanceScreen()
{
    Display_Clear();

    drawHeader();

    drawRPMBar();

    drawRPMText();

    drawInfo();
}

void Display_UpdateRPM()
{
    updateDisplayedRPM();
    drawRPMBar();
    drawRPMText();
}

void Display_UpdateTemperature()
{
    drawInfo();
}

void Display_UpdateBattery()
{
    drawInfo();
}

void Display_UpdateAll()
{
    drawRPMBar();

    drawRPMText();

    drawInfo();
}