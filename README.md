
# JConsole10
JConsole10 is a hand held video game system. The software in this repository contains the drivers and games that are a part of JConsole8. Here is a list of all the JConsole platforms:  

| Platform      | Microcontroller  | BitSize | CPU     |  Memory |  Flash  | 
| ------------- |:----------------:|:-------:|:-------:|:-------:|:-------:|
| JConsole10.   | Atmel SAM3X8E.   | 32-bit. |  84MHz. | 32KB.   | 512 KB. |
| JConsole9     | TM4C-123GH6PM    | 32-bit  |  80MHz  | 32KB    | 256 KB  |
| JConsole8Lim  |  MSP430g2553     | 16-bit  |  16Mhz  | 2KB     | 16 KB   |
| JConsole8     |    MSP432        | 32-bit  |  48MHz  | 64KB    | 128 KB  |
| JConsole6     |   MSP430f5529    | 16-bit  |  25MHz  | 8KB     | 128 KB  |
| JConsole5     |  MSP430g2553     | 16-bit  |  16MHz  | 2KB     | 16 KB   |  


   
## Arduino Due
At the heart of JConsole10 is the Atmel SAM3X8E embedded microcontroller. The SAM3X8E provides a set of timers that are used for various game
events, sound generation, joystick reading, etc.  

## LCD  
JConsole10 uses an ILI9341 based 240 by 320 pixel color LCD. The driver for this device was pulled from Adafruit ILI9341 library. To minimize the
number of IO pins the interface between the MSP432 and ILI9341 is over SPI.  

## Joystick
The joystick provides an X/Y interface for JConsole10. Sampling for the 10-bit ADC is initialized periodically with one of the system timers.
A callback function sets global values after the sampling is complete making this operation run in a separate low level thread asynchronously.
The joystick values are pulled from these global values. The joystick position is computed by splitting each value in half. Dividing each half
into segments is used to compute the magnitude of the joystick position.

## CDS Cell
In addition to pulling joystick ADC values the sampling system pulls values from a CDS Cell. These values are primarily used as part of a random 
number generator. Random numbers are continually being generated and placed in a circular queue. These values are then accessed by the various games
for randomized events.

## Compilation
JConsole10 can be compiled with the Arduino Sketch.

## Status
JConsole10 is currently in active development.
