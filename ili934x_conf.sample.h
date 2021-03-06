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

#ifndef ILI934X_CONF_H
#define ILI934X_CONF_H 1

#define ILI934X_BLC_PIN                 4
#define ILI934X_RESET_PIN               7

#define ILI934X_CMD_ADDR                0x4000
#define ILI934X_DATA_ADDR               0x4100

#define ILI934X_INTERNAL_OSC_CLK        615000

#define ILI934X_DRIVING_LINES           320
#define ILI934X_VERT_FRONT_PORCH        2
#define ILI934X_VERT_BACK_PORCH         2

/* Default MADCTL Settings */
/* Direction defined here will be treated as North */
#define ILI934X_ROW_ADDR_ORDER          1
#define ILI934X_COL_ADDR_ORDER          1
#define ILI934X_ROW_COL_EXCHANGE        1
#define ILI934X_VERT_REFRESH_ORDER      0
#define ILI934X_RGB_BGR_ORDER           1
#define ILI934X_HORZ_REFRESH_ORDER      0

#endif
