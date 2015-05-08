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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../font/font.h"
#include "lcd.h"

void lcd_init() {
  /* Enable extended memory interface with 10 bit addressing */
  XMCRB = _BV(XMM2) | _BV(XMM1);
  XMCRA = _BV(SRE);
  /* Set ILI934X reset pin to output */
  DDRC |= _BV(ILI934X_RESET_PIN);
  /* Set backlight pin to output */
  DDRB |= _BV(ILI934X_BLC_PIN);
  _delay_ms(1);
  /* Reset the display to synchronise initialisation */
  PORTC &= ~_BV(ILI934X_RESET_PIN);
  _delay_ms(20);
  PORTC |= _BV(ILI934X_RESET_PIN);
  _delay_ms(120);
  /* Disable the display while settings are configured */
  ili934_displayOff();
  /* Leave sleep and allow for wake up to to complete */
  ili934_sleepOut();
  _delay_ms(60);
  /* Set GVDD level to 4.75V */
  ili934_powerControl1(0x26);
  /* Set VCOMH to 4.025V & VCOML to -1.925V */
  ili934_vcomControl1(0x35, 0x2E);
  /* Set VCOMH to VMH – 11 and VCOML to VMH – 11 */
  /* TODO: Does this do anything without setting nVM? */
  ili934_vcomControl2(0, 0x35);
  /* Set non-overlap timing control */
  ili934_driverTimingCtrlA(1,0,0,0);
  /* Set RGB Interface Format (DPI) to 16 bits / pixel */
  /* Set MCU Interface Format (DBI) to 16 bits / pixel */
  ili934_pixelFormatSet(0x05, 0x05);
  /* Enable Tearing Effect Line */
  ili934_tearingEffectOn(0);
  /* Enable falling edge detect on External Interrupt Control Register B ISC6 */
  EICRB |= _BV(ISC61);
  /* Enable the LCD backlight */
  PORTB |= _BV(ILI934X_BLC_PIN);
}

void lcd_selectRegion(lcd_region region) {
  ili934_columnAddrSet(region.left, region.right);
  ili934_pageAddrSet(region.top, region.bottom);
  lcd.selection = (region.right - region.left) * (region.bottom - region.top);
}

void lcd_setColour(lcd_colour16 colour) {
  uint16_t i;
  ili934_initMemoryWrite();
  for (i = 0; i < lcd.selection; i++) {
    ili934_write_data16(colour);
  }
}

void lcd_setPixel(lcd_pixel p, lcd_colour16 colour) {
  /* Select the point */
  ili934_columnAddrSet(p.x, p.x);
  ili934_pageAddrSet(p.y, p.y);
  /* Set selection size to 1 */
  lcd.selection = 1;
  /* Write the colour */
  ili934_initMemoryWrite();
  ili934_write_data16(colour);
}

void lcd_setPixels(lcd_pixel *p, lcd_colour16 *colour, uint16_t pixels) {
  uint16_t i;
  /* For each pixel, set pixel */
  for (i = 0; i < pixels; i++) {
    lcd_setPixel(*p++, *colour++);
  }
}

void lcd_setRegion(lcd_region region, lcd_colour16 colour) {
  lcd_selectRegion(region);
  lcd_setPixel(colour);
}

void lcd_setRegions(lcd_region *region, lcd_colour16 *colour, uint16_t regions) {
  uint16_t i;
  /* For each pixel, set pixel */
  for (i = 0; i < regions; i++) {
    lcd_setRegion(*region++, *colour++);
  }
}

void lcd_setBitmap(lcd_region region, lcd_colour16 *colour) {
  /* Select the region */
  lcd_selectRegion(region);
  /* Initialise write process */
  ili934_initMemoryWrite();
  /* Write to all pixels of region */
  for (i = 0; i < lcd.selection; i++) {
    ili934_write_data16(*colour++);
  }
}

void lcd_setBitmap8bit(lcd_region region, lcd_colour8 *colour) {
  /* Select the region */
  lcd_selectRegion(region);
  /* Initialise write process */
  ili934_initMemoryWrite();
  /* Write to all pixels of region */
  for (i = 0; i < lcd.selection; i++) {
    ili934_write_data16(colour_8to16(*colour++));
  }
}

void lcd_setBitmapMono(lcd_region region, uint8_t* data, uint8_t bpc) {
  uint16_t x = 0, y = 0;
  uint16_t i, h, w;
  uint8_t b = 0;
  h = region.bottom - region.top;
  w = region.right - region.left;
  /* Select the region */
  lcd_selectRegion(region);
  ili934_initMemoryWrite();
  for (i = 0; i < lcd.selection; i++) {
    if (*data++ & (1 << b)) {
      ili934_write_data16(lcd.foreground)
    } else {
      ili934_write_data16(lcd.background)
    }
    b = (b + 1) % 8;
    if (y % bpc == 0 || ++y >= h) {
      if (++x >= w) {
        return;
      }
    }
  }
}

void lcd_setRegionFunction(lcd_region region, lcd_colour16 (f*)(uint16_t x, uint16_t), bool realtive) {
  uint16_t x, y;
  uint16_t w, h;
  /* Select the region */
  lcd_selectRegion(region);
  /* Determine the width of the area to write to.
   * Starting point will be 0 if relative and top-left otherwise
   */
  if (relative) {
    h = region.bottom - region.top;
    w = region.right - region.left;
  } else {
    h = region.bottom;
    w = region.right;
  }
  for (x = relative ? 0 : region.left; x < w; x++) {
    for (y = relative ? 0 : region.top; y < w; y++) {
      /* TODO: Check x and y are correct way round */
      ili934_write_data16(f(x,y));
    }
  }
}
