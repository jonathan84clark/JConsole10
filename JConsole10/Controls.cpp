/*******************************************************
* CONTROLS
* DESC: The controls class provides an interface to the
* various controls of JConsole10. Internally it handles
* all button debouncing and system state collections.
* Author: Jonathan L Clark
* Date: 7/16/2019
*******************************************************/
#include <stdio.h>
#include "ILI9341_SPI.h"
#include "Controls.h"
#include <Arduino.h>

#define JOYSTICK_X A10
#define JOYSTICK_Y A11

Controls::Controls()
{
  //Setup Joystick
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
}

void Controls::Update(unsigned long ms_ticks)
{
    joystick.x = analogRead(JOYSTICK_X);
    joystick.y = analogRead(JOYSTICK_Y);
}
