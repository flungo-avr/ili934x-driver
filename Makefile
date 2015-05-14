# The MIT License (MIT)
#
# Copyright (c) 2015, Fabrizio Lungo <fab@lungo.co.uk>
# Copyright (c) 2014-2015 Klaus-Peter Zauner
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Target Architecture
MCU   := at90usb1286
F_CPU := 8000000UL

# Tool Options
CFLAGS       := -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)
CFLAGS       += -Wall -Wextra -pedantic

# Directories
BUILD_DIR    := _build

# Ignoring hidden directories; sorting to drop duplicates:
CFILES       := $(shell find . ! -path "*/\.*" -type f -name "*.c")
CPATHS       := $(sort $(dir $(CFILES)))
vpath %.c $(CPATHS)
HFILES       := $(shell find . ! -path "*/\.*" -type f -name "*.h")
HPATHS       := $(sort $(dir $(HFILES)))
vpath %.h $(HPATHS)
HPATHS       := $(sort $(dir $(HFILES)))
CFLAGS       += $(addprefix -I ,$(HPATHS))
DEPENDENCIES := $(sort $(patsubst %.c,$(BUILD_DIR)/%.d,$(notdir $(CFILES))))
OBJFILES     := $(sort $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(CFILES))))

all: $(OBJFILES)

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	avr-gcc $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

-include $(DEPENDENCIES)

include docs/Doxymake.mk
