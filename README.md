ili934x-driver
==============

Native C implementation for the ILI934X series of LCD drivers. This driver is designed to implement all functionality of the ILI934X display driver for use with AVR based projects. The driver is still a WIP and not all features are completed. The driver provides a set of simple functions for draweing various types of objects to the screen that can be used in conjunction with my AVR Graphics 2D Library to build more complex shapes.

I have tried to implement the library in a lightweight fashion and the footprint of the library alone is extremely small.

More documentation will be added as the library develops.

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
