#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

/**
 * Converts RGB-888 color to RGB-565.
 */
uint16_t color565(const uint8_t r, const uint8_t g, const uint8_t b);
uint16_t color565_s(const uint8_t r, const uint8_t g, const uint8_t b);

/**
 * Prints a chess pattern on the display.
 */
void printPattern(const uint16_t backgroundColor, const uint16_t foregroundColor);
void printPattern_s(const uint16_t backgroundColor, const uint16_t foregroundColor);

/**
 * Initializes cursor properties.
 */
void initCursor();
void initCursor_s();

/**
 * Sets the textwriter cursor.
 */
void setCursor(const int16_t x, int16_t y);
void setCursor_s(const int16_t x, int16_t y);

/**
 * Sets the color of the font in RGB-565 format.
 */
void setTextColor(const uint16_t color);
void setTextColor_s(const uint16_t color);

/**
 * Sets the size of the font.
 */
void setTextSize(const uint8_t s);
void setTextSize_s(const uint8_t s);

/**
 * Sets the color of the font background.
 */
void setBackgroundColor(const int bg);
void setBackgroundColor_s(const int bg);

/**
 * Draws a char c on (x,y).
 * The character is shown in color c, and its background is colored using color bg.
 */
void drawChar(const int x, const int y,  const char c, const int color,  const int bg, const char size);
void drawChar_s(const int x, const int y, const char c, const int color, const int bg, const char size);


/**
 * Draws a char c on the actual cursor position and updates the cursor afterwards.
 */
void writeAuto(const char c);
void writeAuto_s(const char c);

/**
 * Draws a strings on the display with automated cursor update.
 */
void writeText(const char *text);
void writeText_s(const char *text);

/**
 * Draws a string on the display with automated cursor update and linebreak.
 */
void writeTextln(const char *text);
void writeTextln_s(const char *text);

/**
 * Writes a 8 bit variable on the display.
 */
void writeNumberOnDisplay(const uint8_t *value);
void writeNumberOnDisplay_s(const uint8_t *value);

/**
 * Writes a 8 bit variable on the display (right-aligned).
 * This function writes out six right-aligned digits ("65535\0").
 * 
 */
void writeNumberOnDisplayRight(const uint8_t *value);
void writeNumberOnDisplayRight_s(const uint8_t *value);


void write16BitNumberOnDisplay(const uint16_t *value, uint8_t mode);
void write16BitNumberOnDisplay_s(const uint16_t *value, uint8_t mode);

#endif
