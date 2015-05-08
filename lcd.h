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

#include "ili934x.h"
#include "colour/colour.h"
#include <stdbool.h>

typedef enum {
  North = 0,
  West = 90,
  South = 180,
  East = 270
} lcd_orientation;

#define lcd_orientSum(orientA, orientB) ((orientA + orientB) % 360)

typedef struct {
  uint16_t x, y;
} lcd_pixel;

typedef struct {
  uint16_t left, right;
  uint16_t top, bottom;
} lcd_region;

typedef struct {
  uint16_t width, height;
  orientation orient;
  uint16_t selection;
  lcd_colour16 foreground, background;
} lcd;

extern lcd lcd;

void lcd_init();
void lcd_orientation(lcd_orientation orient);
void lcd_brightness(uint8_t i);
void lcd_setFrameRateHz(uint8_t fr);
void lcd_selectRegion(lcd_region region);
void lcd_setColour(lcd_colour16 colour);
void lcd_setPixel(lcd_pixel p, lcd_colour16 colour);
void lcd_setPixels(lcd_pixel* p, lcd_colour16* colour, uint16_t pixels);
void lcd_setRegion(lcd_region region, lcd_colour16 colour);
void lcd_setRegions(lcd_region* region, lcd_colour16* colour, uint16_t regions);
void lcd_setBitmap(lcd_region region, lcd_colour16* colour);
void lcd_setBitmap8bit(lcd_region region, lcd_colour8* colour);
void lcd_setBitmapMono(lcd_region region, lcd_colour16 colour);
void lcd_setRegionFunction(lcd_region region, lcd_colour16 (f*)(uint16_t x, uint16_t), bool realtive);
void lcd_clear();
void lcd_clearPixel(lcd_pixel p);
void lcd_clearPixels(lcd_pixel* p, uint16_t pixels);
void lcd_clearRegion(lcd_region region);
void lcd_clearRegions(lcd_region* region, uint16_t regions);
void lcd_clearRegionFunction(lcd_region region, bool (f*)(uint16_t x, uint16_t), bool realtive);
