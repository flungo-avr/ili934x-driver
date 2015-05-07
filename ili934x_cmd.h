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

/* Command definitions based on version 1.10 of the a-Si TFT LCD Single Chip
 * Driver (240RGBx320 Resolution and 262K color) Specification
 *
 */

/* Level 1 Commands        HEX     Command Function */
#define ILI934X_NOP        0x00 /* No Operation */
#define ILI934X_SWRESET    0x01 /* Software Reset */
#define ILI934X_RDDIDIF    0x04 /* Read Display Identification Information */
#define ILI934X_RDDST      0x09 /* Read Display Status */
#define ILI934X_RDDPM      0x0A /* Read Display Power Mode */
#define ILI934X_RDDMADCTL  0x0B /* Read Display MADCTL */
#define ILI934X_RDDCOLMOD  0x0C /* Read Display Pixel Format */
#define ILI934X_RDDIM      0x0D /* Read Display Image Format */
#define ILI934X_RDDSM      0x0E /* Read Display Signal Mode */
#define ILI934X_RDDSDR     0x0F /* Read Display Self-Diagnostic Result */
#define ILI934X_SLPIN      0x10 /* Enter Sleep Mode */
#define ILI934X_SLPOUT     0x11 /* Sleep OUT */
#define ILI934X_PTLON      0x12 /* Partial Mode ON */
#define ILI934X_NORON      0x13 /* Normal Display Mode ON */
#define ILI934X_INVOFF     0x20 /* Display Inversion OFF */
#define ILI934X_INVON      0x21 /* Display Inversion ON */
#define ILI934X_GAMSET     0x26 /* Gamma Set */
#define ILI934X_DISPOFF    0x28 /* Display OFF */
#define ILI934X_DISPON     0x29 /* Display ON */
#define ILI934X_CASET      0x2A /* Column Address Set */
#define ILI934X_PASET      0x2B /* Page Address Set */
#define ILI934X_RAMWR      0x2C /* Memory Write */
#define ILI934X_RGBSET     0x2D /* Color SET */
#define ILI934X_RAMRD      0x2E /* Memory Read */
#define ILI934X_PTLAR      0x30 /* Partial Area */
#define ILI934X_VSCRDEF    0x33 /* Vertical Scrolling Definition */
#define ILI934X_TEOFF      0x34 /* Tearing Effect Line OFF */
#define ILI934X_TEON       0x35 /* Tearing Effect Line ON */
#define ILI934X_MADCTR     0x36 /* Memory Access Control */
#define ILI934X_VSCRSADD   0x37 /* Vertical Scrolling Start Address */
#define ILI934X_IDMOFF     0x38 /* Idle Mode OFF */
#define ILI934X_IDMON      0x39 /* Idle Mode ON */
#define ILI934X_COLMOD     0x3A /* Pixel Format Set */
#define ILI934X_RAMWRCNT   0x3C /* Write Memory Continue */
#define ILI934X_RAMRDCNT   0x3E /* Read Memory Continue */
#define ILI934X_TSSET      0x44 /* Set Tear Scanline */
#define ILI934X_TSGET      0x45 /* Get Scanline */
#define ILI934X_WRDISBV    0x51 /* Write Display Brightness */
#define ILI934X_RDDISBV    0x52 /* Read Display Brightness */
#define ILI934X_WRCTRLD    0x53 /* Write CTRL Display */
#define ILI934X_RDCTRLD    0x54 /* Read CTRL Display */
#define ILI934X_WRCABC     0x55 /* Write Content Adaptive Brightness Control */
#define ILI934X_RDCABC     0x56 /* Read Content Adaptive Brightness Control */
#define ILI934X_WRCABCMIN  0x5E /* Write CABC Minimum Brightness */
#define ILI934X_RDCABCMIN  0x5F /* READ CABC Minimum Brightness */
#define ILI934X_RDID1      0xDA /* Read ID1 */
#define ILI934X_RDID2      0xDB /* Read ID2 */
#define ILI934X_RDID3      0xDC /* Read ID3 */

/* Level 2 Commands        HEX     Command Function */
#define ILI934X_IFMODE     0xB0 /* RGB Interface Signal Control */
#define ILI934X_FRMCTR1    0xB1 /* Frame Control (In Normal Mode) */
#define ILI934X_FRMCTR2    0xB2 /* Frame Control (In Idle Mode) */
#define ILI934X_FRMCTR3    0xB3 /* Frame Control (In Partial Mode) */
#define ILI934X_INVTR      0xB4 /* Display Inversion Control */
#define ILI934X_PRCTR      0xB5 /* Blanking Porch Control */
#define ILI934X_DISCTRL    0xB6 /* Display Function Control */
#define ILI934X_ETMOD      0xB7 /* Entry Mode Set */
#define ILI934X_BLCTRL1    0xB8 /* Backlight Control 1 */
#define ILI934X_BLCTRL2    0xB9 /* Backlight Control 2 */
#define ILI934X_BLCTRL3    0xBA /* Backlight Control 3 */
#define ILI934X_BLCTRL4    0xBB /* Backlight Control 4 */
#define ILI934X_BLCTRL5    0xBC /* Backlight Control 5 */
#define ILI934X_BLCTRL7    0xBE /* Backlight Control 7 */
#define ILI934X_BLCTRL8    0xBF /* Backlight Control 8 */
#define ILI934X_PWCTRL1    0xC0 /* Power Control 1 */
#define ILI934X_PWCTRL2    0xC1 /* Power Control 2 */
#define ILI934X_PWCTRL3    0xC2 /* Power Control 3 */
#define ILI934X_PWCTRL4    0xC3 /* Power Control 4 */
#define ILI934X_PWCTRL5    0xC4 /* Power Control 5 */
#define ILI934X_VMCTRL1    0xC5 /* VCOM Control 1 */
#define ILI934X_VMCTRL2    0xC7 /* VCOM Control 2 */
#define ILI934X_NVMWR      0xD0 /* NV Memory Write */
#define ILI934X_NVMPKEY    0xD1 /* NV Memory Protection Key */
#define ILI934X_RDNVM      0xD2 /* NV Memory Status Read */
#define ILI934X_RDID4      0xD3 /* Read ID4 */
#define ILI934X_PGAMCTRL   0xE0 /* Positive Gamma Correction */
#define ILI934X_NGAMCTRL   0xE1 /* Negative Gamma Correction */
#define ILI934X_DGAMCTRL1  0xE2 /* Digital Gamma Correction 1 */
#define ILI934X_DGAMCTRL2  0xE3 /* Digital Gamma Correction 2 */
#define ILI934X_IFCTL      0xF6 /* Interface Control */

/* Extended Register Commands */
#define ILI934X_PWCTRLA    0xCB /* Power Control A */
#define ILI934X_PWCTRLB    0xCF /* Power Control B */
#define ILI934X_DRTCTRLA   0xE8 /* Driver Timing Control A */
#define ILI934X_DRTCTRLB   0xEA /* Driver Timing Control B */
#define ILI934X_PWOSC      0xED /* Power on sequence control */
#define ILI934X_EN3G       0xF2 /* Enable 3 Gamma Control */
#define ILI934X_PRCTRL     0xF7 /* Pump Rario Control */
