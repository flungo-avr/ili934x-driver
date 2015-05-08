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

#include "ili934.h"

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
#define ILI934X_MADCTL     0x36 /* Memory Access Control */
#define ILI934X_VSCRSADD   0x37 /* Vertical Scrolling Start Address */
#define ILI934X_IDMOFF     0x38 /* Idle Mode OFF */
#define ILI934X_IDMON      0x39 /* Idle Mode ON */
#define ILI934X_PIXSET     0x3A /* Pixel Format Set */
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

/* Macros to aid use of commands defined using typedefs from ili934.h
 *
 */

/* Level 1 Commands */
#define ili934_noOperation()          ili934_write_cmd(ILI934X_NOP)
#define ili934_softReset()            ili934_write_cmd(ILI934X_SWRESET)
#define ili934_sleepIn()              ili934_write_cmd(ILI934X_SLPIN)
#define ili934_sleepOut()             ili934_write_cmd(ILI934X_SLPOUT)
#define ili934_partialModeOn()        ili934_write_cmd(ILI934X_PTLON)
#define ili934_normalModeOn()         ili934_write_cmd(ILI934X_NORON)
#define ili934_displayInversionOff()  ili934_write_cmd(ILI934X_DINVOFF)
#define ili934_displayInversionOn()   ili934_write_cmd(ILI934X_DINVON)
#define ili934_setGamma(GC)           ili934_write_cmd_data(ILI934X_GAMSET, GC)
#define ili934_displayOff()           ili934_write_cmd(ILI934X_DISPOFF)
#define ili934_displayOn()            ili934_write_cmd(ILI934X_DISPON)
#define ili934_columnAddrSet(SC, EC)  ili934_write_cmd(ILI934X_CASET); \
                                      ili934_write_data(SC); \
                                      ili934_write_data(EC)
#define ili934_pageAddrSet(SP, EP)    ili934_write_cmd(ILI934X_PASET); \
                                      ili934_write_data(SP); \
                                      ili934_write_data(EP)
#define ili934_initMemoryWrite()      ili934_write_cmd(ILI934X_RAMWR)
#define ili934_partialArea(SR, ER)    ili934_write_cmd(ILI934X_PLTAR); \
                                      ili934_write_data(SR); \
                                      ili934_write_data(ER)
#define ili934_initMemoryRead()       ili934_write_cmd(ILI934X_RAMRD)
#define ili934_vertScrollDef(TFA, VSA, BFA) \
                                      ili934_write_cmd(ILI934X_VSCRDEF); \
                                      ili934_write_data(TFA); \
                                      ili934_write_data(VSA); \
                                      ili934_write_data(BFA)
#define ili934_tearingEffectOff()     ili934_write_cmd(ILI934X_TEOFF)
#define ili934_tearingEffectOn(M)     ili934_write_cmd_data(ILI934X_TEOFF, M)
#define ili934_memoryAccessControl(MY, MX, MV, ML, BGR, MH) \
                                      ili934_write_cmd(ILI934X_MADCTL); \
                                      ili934_write_data(MY << 7 | MX << 6 | MV << 5 | ML << 4 | BGR << 3 | MH << 2)
#define ili934_vertScrollStartAddr(VSP) \
                                      ili934_write_cmd_data(ILI934X_VSCRSADD, VSP)
#define ili934_idleModeOff()          ili934_write_cmd(ILI934X_IDMOFF)
#define ili934_idleModeOn()           ili934_write_cmd(ILI934X_IDMON)
#define ili934_pixelFormatSet(DPI, DBI) \
                                      ili934_write_cmd(ILI934X_PIXSET); \
                                      ili934_write_data(DPI << 4 | DBI)
#define ili934_continueMemoryWrite()  ili934_write_cmd(ILI934X_RAMWRCNT)
#define ili934_continueMemoryRead()   ili934_write_cmd(ILI934X_RAMRDCNT)
#define ili934_setTearScanline(STS)   ili934_write_cmd_data16(ILI934X_TSSET, STS)
#define ili934_setBrightness(DBV)     ili934_write_cmd_data(ILI934X_WRDISBV, DBV)
#define ili934_setBrightnessCtrl(BCTRL, DD, BL) \
                                      ili934_write_cmd(ILI934X_WRCTRLD); \
                                      ili934_write_data(BCTRL << 5 | DD << 3 | BL << 2)
#define ili934_setCABC(CC)            ili934_write_cmd_data(ILI934X_WRCABC, CC)
#define ili934_setCABCMin(CMB)        ili934_write_cmd_data(ILI934X_WRCABCMIN, CMB)

/* Level 2 Commands */
#define ili934_setInterfaceMode(BPM, RCM, VSPL, HSPL, DPL, EPL) \
                                      ili934_write_cmd_data(ILI934X_IFMODE); \
                                      ili934_write_data(BPM << 7 | RCM << 5 | VSPL << 3 | HSPL << 2 | DPL << 1 | EPL)
#define ili934_setNormalFrameRateCtrl(DIVA, RTNA) \
                                      ili934_write_cmd(ILI934X_FRMCTR1); \
                                      ili934_write_data(DIVA); \
                                      ili934_write_data(RTNA)
#define ili934_setIdleFrameRateCtrl(DIVB, RTNB) \
                                      ili934_write_cmd_data16(ILI934X_FRMCTR2); \
                                      ili934_write_data(DIVB); \
                                      ili934_write_data(RTNB)
#define ili934_setPartialFrameRateCtrl(DIVC, RTNC) \
                                      ili934_write_cmd_data16(ILI934X_FRMCTR3); \
                                      ili934_write_data(DIVC); \
                                      ili934_write_data(RTNC)
#define ili934_setInversionCtrl(NLA, NLB, NLC) \
                                      ili934_write_cmd(ILI934X_INVTR); \
                                      ili934_write_data(NLA << 2 | NLB << 1 | NLC)
#define ili934_setBlankingPorch(VFP, VBP, HFP, HBP) \
                                      ili934_write_cmd_data16(ILI934X_PRCTR); \
                                      ili934_write_data(VFP); \
                                      ili934_write_data(VBP); \
                                      ili934_write_data(HFP); \
                                      ili934_write_data(HBP)
#define ili934_setDisplayFunction(PTG, PT, REV, GS, SS, SM, ISC, NL, PCDIV) \
                                      ili934_write_cmd(ILI934X_DISCTRL); \
                                      ili934_write_data(PTG << 2 | PT); \
                                      ili934_write_data(REV << 7 | GS << 6 | SS << 5 | SM << 4 | ISC); \
                                      ili934_write_data(NL); \
                                      ili934_write_data(PCDIV)
#define ili934_setEntryMode(GON, DTE, GAS) \
                                      ili934_write_cmd(ILI934X_ETMOD); \
                                      ili934_write_data(GON << 2 | DTE << 1 | GAS)
#define ili934_setBacklightCtrl1(TH_UI) \
                                      ili934_write_cmd_data(ILI934X_BLCTRL1, TH_UI)
#define ili934_setBacklightCtrl2(TH_MV, TH_ST) \
                                      ili934_write_cmd(ILI934X_BLCTRL2); \
                                      ili934_write_data(TH_MV << 4 | TH_ST)
#define ili934_setBacklightCtrl3(DTH_UI) \
                                      ili934_write_cmd_data(ILI934X_BLCTRL3, DTH_UI)
#define ili934_setBacklightCtrl4(DTH_MV, DTH_ST) \
                                      ili934_write_cmd(ILI934X_BLCTRL4); \
                                      ili934_write_data(DTH_MV << 4 | DTH_ST)
#define ili934_setBacklightCtrl5(DIM2, DIM1) \
                                      ili934_write_cmd(ILI934X_BLCTRL4); \
                                      ili934_write_data(DIM2 << 4 | DIM1)
#define ili934_setBacklightCtrl7(PWM_DIV) \
                                      ili934_write_cmd_data(ILI934X_BLCTRL7, PWM_DIV)
#define ili934_setBacklightCtrl5(LEDONR, LEDONPOL, LEDPWMPOL) \
                                      ili934_write_cmd(ILI934X_BLCTRL4); \
                                      ili934_write_data(LEDONR << 2 | LEDONPOL << 1 | LEDPWMPOL)
#define ili934_powerControl1(VRH)     ili934_write_cmd_data(ILI934X_PWCTRL1, VRH)
#define ili934_powerControl2(BT)      ili934_write_cmd_data(ILI934X_PWCTRL2, BT)
#define ili934_vcomControl1(VMH, VML) ili934_write_cmd(ILI934X_VMCTRL1); \
                                      ili934_write_data(VMH); \
                                      ili934_write_data(VML)
#define ili934_vcomControl2(nVM, VMF) ili934_write_cmd(ILI934X_VMCTRL2); \
                                      ili934_write_data(nVM << 7 | VMF);
#define ili934_nvMemoryWrite(PGM_ADR, PGM_DATA) \
                                      ili934_write_cmd(ILI934X_NVMWR); \
                                      ili934_write_data(PGM_ADDR); \
                                      ili934_write_data(PGM_DATA)
#define ili934_nvMemoryProtectionKey(KEY) \
                                      ili934_write_cmd(ILI934X_NVMPKEY); \
                                      ili934_write_data((KEY >> 16) & 0xFF); \
                                      ili934_write_data((KEY >> 8) & 0xFF); \
                                      ili934_write_data(KEY & 0xFF)
#define ili934_setPositiveGammaCorrection(VP63, VP62, VP61, VP59, VP57, VP50, VP43, VP27, VP36, VP20, VP13, VP6, VP4, VP2, VP1, VP0) \
                                      ili934_write_cmd(ILI934X_PGAMCTRL); \
                                      ili934_write_data(VP63); \
                                      ili934_write_data(VP62); \
                                      ili934_write_data(VP61); \
                                      ili934_write_data(VP59); \
                                      ili934_write_data(VP57); \
                                      ili934_write_data(VP50); \
                                      ili934_write_data(VP43); \
                                      ili934_write_data(VP27 << 4 | VP36); \
                                      ili934_write_data(VP20); \
                                      ili934_write_data(VP13); \
                                      ili934_write_data(VP6); \
                                      ili934_write_data(VP4); \
                                      ili934_write_data(VP2); \
                                      ili934_write_data(VP1); \
                                      ili934_write_data(VP0)
#define ili934_setPositiveGammaCorrection(VN63, VN62, VN61, VN59, VN57, VN50, VN43, VN27, VN36, VN20, VN13, VN6, VN4, VN2, VN1, VN0) \
                                      ili934_write_cmd(ILI934X_PGAMCTRL); \
                                      ili934_write_data(VN63); \
                                      ili934_write_data(VN62); \
                                      ili934_write_data(VN61); \
                                      ili934_write_data(VN59); \
                                      ili934_write_data(VN57); \
                                      ili934_write_data(VN50); \
                                      ili934_write_data(VN43); \
                                      ili934_write_data(VN27 << 4 | VN36); \
                                      ili934_write_data(VN20); \
                                      ili934_write_data(VN13); \
                                      ili934_write_data(VN6); \
                                      ili934_write_data(VN4); \
                                      ili934_write_data(VN2); \
                                      ili934_write_data(VN1); \
                                      ili934_write_data(VN0)
#define ili934_setPositiveGammaCorrection(RCA, BCA) \
                                      ili934_write_cmd(ILI934X_PGAMCTRL); \
                                      ili934_write_data(RCA[0] | BCA[0]); \
                                      ili934_write_data(RCA[1] | BCA[1]); \
                                      ili934_write_data(RCA[2] | BCA[2]); \
                                      ili934_write_data(RCA[3] | BCA[3]); \
                                      ili934_write_data(RCA[4] | BCA[4]); \
                                      ili934_write_data(RCA[5] | BCA[5]); \
                                      ili934_write_data(RCA[6] | BCA[6]); \
                                      ili934_write_data(RCA[7] | BCA[7]); \
                                      ili934_write_data(RCA[8] | BCA[8]); \
                                      ili934_write_data(RCA[9] | BCA[9]); \
                                      ili934_write_data(RCA[10] | BCA[10]); \
                                      ili934_write_data(RCA[11] | BCA[11]); \
                                      ili934_write_data(RCA[12] | BCA[12]); \
                                      ili934_write_data(RCA[13] | BCA[13]); \
                                      ili934_write_data(RCA[14] | BCA[14]); \
                                      ili934_write_data(RCA[15] | BCA[15]); \
                                      ili934_write_data(RCA[16] | BCA[16]); \
                                      ili934_write_data(RCA[17] | BCA[17]); \
                                      ili934_write_data(RCA[18] | BCA[18]); \
                                      ili934_write_data(RCA[19] | BCA[19]); \
                                      ili934_write_data(RCA[20] | BCA[20]); \
                                      ili934_write_data(RCA[21] | BCA[21]); \
                                      ili934_write_data(RCA[22] | BCA[22]); \
                                      ili934_write_data(RCA[23] | BCA[23]); \
                                      ili934_write_data(RCA[24] | BCA[24]); \
                                      ili934_write_data(RCA[25] | BCA[25]); \
                                      ili934_write_data(RCA[26] | BCA[26]); \
                                      ili934_write_data(RCA[27] | BCA[27]); \
                                      ili934_write_data(RCA[28] | BCA[28]); \
                                      ili934_write_data(RCA[29] | BCA[29]); \
                                      ili934_write_data(RCA[30] | BCA[30]); \
                                      ili934_write_data(RCA[31] | BCA[31]); \
                                      ili934_write_data(RCA[32] | BCA[32]); \
                                      ili934_write_data(RCA[33] | BCA[33]); \
                                      ili934_write_data(RCA[34] | BCA[34]); \
                                      ili934_write_data(RCA[35] | BCA[35]); \
                                      ili934_write_data(RCA[36] | BCA[36]); \
                                      ili934_write_data(RCA[37] | BCA[37]); \
                                      ili934_write_data(RCA[38] | BCA[38]); \
                                      ili934_write_data(RCA[39] | BCA[39]); \
                                      ili934_write_data(RCA[40] | BCA[40]); \
                                      ili934_write_data(RCA[41] | BCA[41]); \
                                      ili934_write_data(RCA[42] | BCA[42]); \
                                      ili934_write_data(RCA[43] | BCA[43]); \
                                      ili934_write_data(RCA[44] | BCA[44]); \
                                      ili934_write_data(RCA[45] | BCA[45]); \
                                      ili934_write_data(RCA[46] | BCA[46]); \
                                      ili934_write_data(RCA[47] | BCA[47]); \
                                      ili934_write_data(RCA[48] | BCA[48]); \
                                      ili934_write_data(RCA[49] | BCA[49]); \
                                      ili934_write_data(RCA[50] | BCA[50]); \
                                      ili934_write_data(RCA[51] | BCA[51]); \
                                      ili934_write_data(RCA[52] | BCA[52]); \
                                      ili934_write_data(RCA[53] | BCA[53]); \
                                      ili934_write_data(RCA[54] | BCA[54]); \
                                      ili934_write_data(RCA[55] | BCA[55]); \
                                      ili934_write_data(RCA[56] | BCA[56]); \
                                      ili934_write_data(RCA[57] | BCA[57]); \
                                      ili934_write_data(RCA[58] | BCA[58]); \
                                      ili934_write_data(RCA[59] | BCA[59]); \
                                      ili934_write_data(RCA[60] | BCA[60]); \
                                      ili934_write_data(RCA[61] | BCA[61]); \
                                      ili934_write_data(RCA[62] | BCA[62]); \
                                      ili934_write_data(RCA[63] | BCA[63])
#define ili934_setInterfaceCtrl(MY_EOR, MX_EOR, MV_EOR, BGR_EOR, WEMODE, EPF, MDT, ENDIAN, DM, RM, RIM) \
                                      ili934_write_cmd(ILI934X_IFCTL); \
                                      ili934_write_data(MY_EOR << 7 | MX_EOR << 6 | MV_EOR << 5 | BGR_EOR << 3 | WEMODE); \
                                      ili934_write_data(EPF << 4 | MDT); \
                                      ili934_write_data(ENDIAN << 5 | DM << 2 | RM << 1 | RIM)

/* Extended Register Commands */
#define ili934_powerControlA(REG_VD, VBC) \
                                      ili934_write_cmd(ILI934X_PWCTRLA); \
                                      ili934_write_data(0x39); \
                                      ili934_write_data(0x2C); \
                                      ili934_write_data(0x00); \
                                      ili934_write_data(0x30 | REG_VD); \
                                      ili934_write_data(VBC)
#define ili934_powerControlB(PC, DC_ena) \
                                      ili934_write_cmd(ILI934X_PWCTRLB); \
                                      ili934_write_data(0x00); \
                                      ili934_write_data(0x81 | PC << 3)
#define ili934_driverTimingCtrlA(NOW, EQ, CR, PC) \
                                      ili934_write_cmd(ILI934X_DRTCTRLA); \
                                      ili934_write_data(0x84 | NOW); \
                                      ili934_write_data(EQ << 4 | CR); \
                                      ili934_write_data(0x78 | PC)
#define ili934_driverTimingCtrlB(VG_SW_T4, VG_SW_T3, VG_SW_T2, VG_SW_T1) \
                                      ili934_write_cmd(ILI934X_DRTCTRLB); \
                                      ili934_write_data(VG_SW_T4 << 6 | VG_SW_T3 << 4 | VG_SW_T2 << 2 | VG_SW_T1); \
                                      ili934_write_data(0x00)
#define ili934_powerOnSequenceCtrl(CP1, CP23, En_vcl, En_ddvdh, En_vgh, En_vgl, DDVDH_ENH) \
                                      ili934_write_cmd(ILI934X_PWOSC); \
                                      ili934_write_data(0x24 | CP1 << 4 | CP23); \
                                      ili934_write_data(En_vcl << 4 | En_ddvdh); \
                                      ili934_write_data(En_vgh << 4 | En_vgl); \
                                      ili934_write_data(0x01 | DDVDH_ENH)
#define ili934_enable3G(enb_3G) \
                                      ili934_write_cmd(ILI934X_EN3G); \
                                      ili934_write_data(0x02 | enb_3G)
#define ili934_pumpRatioCtrl(Ratio) \
                                      ili934_write_cmd(ILI934X_PRCTRL); \
                                      ili934_write_data(Ratio << 4)
