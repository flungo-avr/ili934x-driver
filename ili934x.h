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

#include <stdbool.h>
#include "ili934x_conf.h"

#ifndef ILI934X_LIB_ILI934XH
#define ILI934X_LIB_ILI934XH 1

#define ili934x_write_cmd(cmd) \
  asm volatile("sts %0,%1" :: "i" (ILI934X_CMD_ADDR), "r" (cmd) : "memory");
#define ili934x_write_data(data) \
  asm volatile("sts %0,%1" :: "i" (ILI934X_DATA_ADDR), "r" (data) : "memory");
#define ili934x_write_data16(data) \
  asm volatile("sts %0,%B1 \n\t sts %0,%A1" :: "i" (ILI934X_DATA_ADDR), "r" (data)  : "memory");
#define ili934x_write_cmd_data(cmd, data) \
  asm volatile("sts %0,%1 \n\t sts %2,%3" :: "i" (ILI934X_CMD_ADDR), "r" (cmd), "i" (ILI934X_DATA_ADDR), "r" (data)  : "memory");

#endif
