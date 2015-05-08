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
