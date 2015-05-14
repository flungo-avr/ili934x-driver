/* The MIT License (MIT)
 *
 * Copyright (c) 2015, Steve Gunn
 * Copyright (c) 2015, Fabrizio Lungo <fab@lungo.co.uk>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

/**
 * @file lcd.h
 * @author Fabrizio Lungo <fab@lungo.co.uk>
 * @brief Methods for an LCD that uses the ILI934X display driver.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "ili934x.h"
#include "ili934x_cmd.h"
#include "lcd_colour.h"
#include "lcd_colour_basic.h"

#ifndef ILI934X_LIB_LCD_H
#define ILI934X_LIB_LCD_H 1

#if ! ILI934X_ROW_COL_EXCHANGE
  /**
   * Width of the LCD Display in pixels at the default orientation.
   */
  #define LCD_WIDTH  240
  /**
   * Height of the LCD Display in pixels at the default orientation.
   */
  #define LCD_HEIGHT 320
#else
  /* Exchange the wdith and height when row and col are swapped */
  #define LCD_WIDTH  320
  #define LCD_HEIGHT 240
#endif

typedef enum {
  North = 0,
  West = 90,
  South = 180,
  East = 270
} lcd_orientation;

#define lcd_orientSum(orientA, orientB) ((orientA + orientB) % 360)

typedef struct {
  uint16_t x, y;
} lcd_point;

typedef struct {
  uint16_t left, right;
  uint16_t top, bottom;
} lcd_region;

typedef struct {
  uint16_t width, height;
  lcd_orientation orient;
  lcd_region selection;
  lcd_colour16 foreground, background;
} lcd_display;

/**
 * Globally accessible lcd_display structure for the LCD display connected
 */
extern lcd_display lcd;

/**
 * Initialise the LCD and setup the lcd_display structure. Uses the
 * configuration to set up the display in a default state. When method returns,
 * display is not on and will need to be activated with lcd_displayOn(). This
 * allows you to perform any further configuration tasks at runtime before the
 * display is enabled or to prepare the display at an earlier stage to activate
 * later.
 *
 * @see lcd_display
 *
 */
void lcd_init();

/**
 * Turns on the display and enables the backlight.
 */
void lcd_displayOn();
/**
 * Turns off the display and disables the backlight.
 */
void lcd_displayOff();

/**
 * Set the current orientation of the display. When the orientation is changed,
 * the screen is cleared.
 *
 * @param[in] orient The orientation to set the display to
 */
void lcd_setOrientation(lcd_orientation orient);

/**
 * Set the brightness level of the display.
 *
 * @param[in] br the brightness as a value from `0` to `255` where `255` is the
 *               brightest
 */
void lcd_setBrightness(uint8_t br);

/**
 * Set the framerate of the display in Hz. Calculates the configuration to
 * provide the framerate that is closest to the desired framerate given in
 * hertz (Hz).
 *
 * @param[in] mode The mode you want to set the framerate for.
 * @param[in] fr   The desired framerate in Hz.
 * @see ili934x_mode
 */
void lcd_setFrameRateHz(ili934x_mode mode, uint8_t fr);

/**
 * Sets the selected region of the display. lcd_setColour(lcd_colour16) can then
 * be used to change the colour of this region.
 *
 * @param[in] region the region of the display to be selected
 */
void lcd_selectRegion(lcd_region region);

/**
 * Sets the colour of the last selected region. Provides a slight performance
 * buff over setRegion as the region does not have to be reselected in order to
 * change the colour. Has limited use case since it can only be applied to the
 * last selected region
 *
 * @param[in] colour the colour to set the previously selected region to
 */
void lcd_setColour(lcd_colour16 colour);

/**
 * Set an individual pixel to a specific colour.
 *
 * @param p      the co-ordinates of the pixel to colour from the top left corner of
 *               the display
 * @param colour the colour to set the pixel to
 */
void lcd_setPixel(lcd_point p, lcd_colour16 colour);

/**
 * Maps an array of pixels to the colours in an array of colours. For each point
 * `p` with index `i` the pixel will be coloured with the colour with the
 * corresponding colour of index `i` from the `colours` array. Both `p` and
 * `colours` should have at least `np` elements.
 *
 * @param p       pointer to the first element in an array of points
 * @param colours pointer to the first element in an array of colours
 * @param np      the number of points in the array
 */
void lcd_setPixels(lcd_point *p, lcd_colour16 *colours, uint16_t np);
/**
 * Maps an array of pixels to the colours in an array of colours. For each point
 * `p` with index `i` the pixel will be coloured with the colour with the
 * corresponding colour of index `i` from the `colours` array. Both `p` and
 * `colours` should have at least `np` elements.
 *
 * For large arrays of points, using 8-bit colour will reduce the memory
 * overhead.
 *
 * @param p       pointer to the first element in an array of points
 * @param colours pointer to the first element in an array of colours
 * @param np      the number of points in the array
 */
void lcd_setPixels8bit(lcd_point *p, lcd_colour8 *colours, uint16_t np);
/**
 * Colours all of the pixels in the array `p` in the colour `colour`. The length
 * of the array `p` should be at least `np` elements long.
 *
 * @param p       pointer to the first element in an array of points
 * @param colour the colour to set the pixels to
 * @param np      the number of points in the array
 */
void lcd_setPixelsMono(lcd_point *p, lcd_colour16 colour, uint16_t np);

/**
 * Sets the colour of a given region.
 *
 * @param[in] region the region to set the colour for
 * @param[in] colour the colour to set the region to
 */
void lcd_setRegion(lcd_region region, lcd_colour16 colour);

/**
 * Maps the colours of an array of colours to an array of regions. For each
 * region `r` with index `i` the region will be coloured with the colour with
 * the corresponding colour of index `i` from the `colours` array. Both `region`
 * and `colours` should have at least `np` elements.
 *
 * @param[in] region pointer to the first element of the array of regions to
 *                   colour
 * @param[in] colour pointer to the first element of the array of colours to map
 *                   to regions
 * @param[in] np     the number of regions in the array
 */
void lcd_setRegions(lcd_region *region, lcd_colour16 *colour, uint16_t nr);
/**
 * Maps the colours of an array of colours to an array of regions. For each
 * region `r` with index `i` the region will be coloured with the colour with
 * the corresponding colour of index `i` from the `colours` array. Both `region`
 * and `colours` should have at least `np` elements.
 *
 * @param[in] region pointer to the first element of the array of regions to
 *                   colour
 * @param[in] colour pointer to the first element of the array of 8 bit colours
 *                   to map to regions
 * @param[in] np     the number of regions in the array
 */
void lcd_setRegions8bit(lcd_region *region, lcd_colour8 *colour, uint16_t nr);

/**
 * Colours all of the regions in the array `region` in the colour `colour`.
 *
 * The length of the array `p` should be at least `np` elements long.
 *
 * @param[in] region pointer to the first element in an array of points
 * @param[in] colour the colour to set the pixels to
 * @param[in] np     the number of points in the array
 */
void lcd_setRegionsMono(lcd_region *region, lcd_colour16 colour, uint16_t nr);

/**
 * Displays a bitmap to a given region.
 *
 * For each pixel in the region (going from left to right before wrapping
 * around) the next colour in the array of colours will be used. Every pixel
 * will be set, so this cannot be used for for any graphic that will not fit
 * in a square.
 *
 * The `colour` array should have at least `(region.right - region.left) *
 * (region.bottom - region.top)` (i.e. `region.height * region.width` - the area
 * of the region in pixels) elements.
 *
 * @param[in] region the region that will be filled with the bit map
 * @param[in] colour pointer to the first element in the map of 16 bit colours
 */
void lcd_setBitmap(lcd_region region, lcd_colour16 *colour);
/**
 * Displays an 8-bit bitmap to a given region.
 *
 * For each pixel in the region (going from left to right before wrapping
 * around) the next colour in the array of colours will be used. Every pixel
 * will be set, so this cannot be used for for any graphic that will not fit
 * in a square.
 *
 * The `colour` array should have at least `(region.right - region.left) *
 * (region.bottom - region.top)` (i.e. `region.height * region.width` - the area
 * of the region in pixels) elements.
 *
 * @param[in] region the region that will be filled with the bit map
 * @param[in] colour pointer to the first element in the map of 8 bit colour
 */
void lcd_setBitmap8bit(lcd_region region, lcd_colour8 *colour);
/**
 * Displays a mono bitmap to a given region.
 *
 * For each pixel in the region (going from left to right before wrapping
 * around) one bit of the data will be read (from LSB to MSB) and if that bit is
 * a `1` forground will be displayed and if it is a `0` background will be used.
 * Foreground and background are based on that defined in the `lcd_display`.
 *
 * `bpr` defines how many bits should be used per row. This allows for better
 * use of the available bits when the width of the region is not divisible by 8.
 * When the width of the region is less than the `bpr` value, then background
 * will be writen into the rest of the given region's width. When `bpr` is
 * greater than the width of the given region, additional bits of data will be
 * ignored.
 *
 * @param[in] region the region that will be filled with the bit map
 * @param[in] data   the pointer to the first byte of the bitmap data
 */
void lcd_setBitmapMono(lcd_region region, uint8_t *data, uint8_t bpr);

void lcd_setRegionFunction(lcd_region region, lcd_colour16 (*f)(uint16_t x, uint16_t), bool relative);
void lcd_clear();
void lcd_clearPixel(lcd_point p);
void lcd_clearPixels(lcd_point *p, uint16_t np);
void lcd_clearRegion(lcd_region region);
void lcd_clearRegions(lcd_region *region, uint16_t nr);
void lcd_clearRegionFunction(lcd_region region, bool (*f)(uint16_t x, uint16_t), bool relative);

#endif
