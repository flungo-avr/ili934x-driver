ili934x-driver
==============

Native C implementation for the ILI934X series of LCD drivers. This driver is designed to implement all functionality of the ILI934X display driver for use with AVR based projects. The driver is still a WIP and not all features are completed. The driver provides a set of simple functions for draweing various types of objects to the screen that can be used in conjunction with my AVR Graphics 2D Library to build more complex shapes.

I have tried to implement the library in a lightweight fashion and the footprint of the library alone is extremely small.

More documentation will be added as the library develops.

Usage
-----

### Compatability/Constraints

This library is designed for use with AVR that support extended memory interface with 10 bit addressing connected to the ILI934X driver via an 8 bit parrallel data bus. This is not planned to be customisable in the forseable future but may be part of the long term roadmap to implement SPI and 16/18bit bus support.

### Configuration

To configure, you will need to have a file names `ili934x_conf.h` in your build path. A sample of this is provided as `ili934x_conf.sample.h`. Configuration is made by defining macros for settings that will enable or disable features.

The configuration options currently include:

-	**ILI934X_BLC_PIN** - The backlight pin used for the LCD Driver, currently assumed to be on `PORTB`
-	**ILI934X_RESET_PIN** - The reset pin used for the LCD Driver, currently assumed to be on `PORTC`
-	**ILI934X_CMD_ADDR** - The address to write 8 bit commands to that will be sent to the LCD Driver via the extended memory interface
-	**ILI934X_DATA_ADDR** - The address to write data (command parameters) to that will be sent to the LCD Driver via the extended memory interface

Libraries
---------

This driver is designed to be expanded with the use of additional libraries to provide the functionality you need. Libraries which I have created for use with this driver include:

-	AVR Text Library - A library to provide text output to the display in a variety of fonts and styles
-	AVR Graphics 2D Library - A library to aid with the drawing of 2D graphics in an efficient manner
-	AVR Graphing Library - A library to plot various types of graphs

Example projects
----------------

Example projects that use this library will be added soon.

Planned features
----------------

Features currently in development include:

-	GRAM read functionality
-	Hardware scrolling
