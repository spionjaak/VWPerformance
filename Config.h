#ifndef CONFIG_H
#define CONFIG_H


// =============================
// TEST MODE
// =============================

#define RPM_TEST_MODE false

// =============================
// TFT PINS
// =============================

#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4

// =============================
// FIRMWARE
// =============================

#define FW_VERSION "v1.0.3"

// =============================
// SCREEN
// =============================

#define SCREEN_WIDTH   320
#define SCREEN_HEIGHT  240

// =============================
// RPM BAR
// =============================

#define MAX_RPM 6000

#define BAR_X 10
#define BAR_Y 80

#define BAR_SEGMENTS 20

#define BAR_SEGMENT_WIDTH 13
#define BAR_SEGMENT_HEIGHT 20

#define BAR_GAP 2

#define BAR_GREEN_LIMIT 12
#define BAR_YELLOW_LIMIT 16

// =============================
// COLORS
// =============================

#define COLOR_BACKGROUND  ILI9341_BLACK
#define COLOR_TEXT        ILI9341_WHITE
#define COLOR_GREEN       ILI9341_GREEN
#define COLOR_YELLOW      ILI9341_YELLOW
#define COLOR_RED         ILI9341_RED
#define COLOR_INFO        ILI9341_CYAN
#define COLOR_DARKGREY    ILI9341_DARKGREY
#define COLOR_LIGHTGREY    ILI9341_LIGHTGREY

#endif