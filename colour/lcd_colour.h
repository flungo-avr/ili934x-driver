/* The MIT License (MIT)
 *
 * Copyright (c) 2015 Fabrizio Lungo <fab@lungo.co.uk>
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

#include <stdint.h>

#ifndef ILI934X_LIB_LCD_COLOUR
  #define ILI934X_LIB_LCD_COLOUR 1

  /* 16 bit colour (5-6-5) */
  typedef uint16_t lcd_colour16;
  /* 8 bit colour (3-3-2) */
  typedef uint8_t  lcd_colour8;

  #define colour_rgb(r, g, b) (((r >> 3) << 5 | (g >> 2)) << 6) | (b >> 3)
  #define colour_hex(hex) colour_rgb((hex & 0xFF0000) >> 16, (hex & 0x00FF00) >> 8, (hex & 0x0000FF))
  #define colour_8to16(col8) (((col8 & 0xE0) << 13) | ((col8 & 0x1C) << 8) | ((col8 & 0x03) << 3))
#endif
