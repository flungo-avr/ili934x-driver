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

typedef enum {
  North = 0,
  West = 90,
  South = 180,
  East = 270
} lcd_orientation;

#define lcd_orientSum(orientA, orientB) ((orientA + orientB) % 360)

typedef struct {
  uint16_t left, right;
  uint16_t top, bottom;
} lcd_region;

typedef struct {
  uint16_t width, height;
  orientation orient;
  uint16_t x, y;
  uint16_t foreground, background;
} lcd;

extern lcd lcd;

void lcd_init();
