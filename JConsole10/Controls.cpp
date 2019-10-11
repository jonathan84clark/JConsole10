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

#define JOYSTICK_CTR 512.0
#define DEAD_ZONE 0.05
#define NEG_DEAD_ZONE -0.05

#define JOYSTICK_X A10
#define JOYSTICK_Y A11
#define LEFT_RIGHT_TILT A2

Controls::Controls()
{
  //Setup Joystick
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(LEFT_RIGHT_TILT, INPUT);

}

/***********************************************
* APPLY DEAD ZONE
* DESC: Creates a dead zone to prevent the joystick
* from drifting.
***********************************************/
float Controls::ApplyDeadZone(float inValue)
{
    if (inValue < 0.0 && inValue > NEG_DEAD_ZONE)
    {
        inValue = 0.0;
    }
    else if (inValue > 0.0 && inValue < DEAD_ZONE)
    {
       inValue = 0.0;
    }
    return inValue;
}

void Controls::Update(unsigned long ms_ticks)
{
   float xValue = (JOYSTICK_CTR - (float)analogRead(JOYSTICK_X)) / JOYSTICK_CTR;
   float yValue = (JOYSTICK_CTR - (float)analogRead(JOYSTICK_Y)) / JOYSTICK_CTR;
   joystick.x = ApplyDeadZone(xValue);
   joystick.y = ApplyDeadZone(yValue);
}
