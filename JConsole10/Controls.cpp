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

// Control defines
#define JOYSTICK_X A10
#define JOYSTICK_Y A11
#define BTN0 7
#define BTN1 6
#define BTN2 5
#define BTN3 4
#define JOY_BTN 18

#define CDS_CELL A3

// Joystick X Positions
#define JOYSTICK_LEFT 1024
#define JOYSTICK_CTR 493
#define JOYSTICK_LEFT_MAG (float)(JOYSTICK_LEFT - JOYSTICK_CTR)
#define JOYSTICK_RIGHT 0
#define JOYSTICK_RIGHT_MAG (float)(JOYSTICK_RIGHT - JOYSTICK_CTR);

// Joystick Y Positions
#define JOYSTICK_UP 1024
#define JOYSTICK_YCTR 493
#define JOYSTICK_UP_MAG (float)(JOYSTICK_UP - JOYSTICK_YCTR)
#define JOYSTICK_DOWN 0
#define JOYSTICK_DOWN_MAG (float)(JOYSTICK_DOWN - JOYSTICK_YCTR);

// Gyro Positions
#define LEFT_RIGHT_TILT A2
#define MIN_TILT_POS 400
#define MAX_TILT_POS 600
#define CTR_TILT 500
#define FORWARD_BACK_GYRO A1

Controls::Controls()
{
  //Setup Joystick
  random_index = 0;
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
  pinMode(CDS_CELL, INPUT);
  pinMode(BTN0, INPUT);
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BTN3, INPUT);
  pinMode(LEFT_RIGHT_TILT, INPUT);
  pinMode(FORWARD_BACK_GYRO, INPUT);
  pinMode(JOY_BTN, INPUT);
}

void Controls::UpdateJoystick()
{
   int joystickX = analogRead(JOYSTICK_X);
   int joystickY = analogRead(JOYSTICK_Y);
   // Convert the joystick value to a scaler
   if (joystickX > JOYSTICK_CTR)
   {
       joystick.x = (float)(joystickX - JOYSTICK_CTR) / JOYSTICK_LEFT_MAG * -1.0;
   }
   else
   {
       joystick.x = (float)(joystickX - JOYSTICK_CTR) / JOYSTICK_RIGHT_MAG;
   }

   // Convert the joystick Y value to a scaler
   if (joystickY > JOYSTICK_YCTR)
   {        
       joystick.y = (float)(joystickY - JOYSTICK_YCTR) / JOYSTICK_DOWN_MAG;
   }
   else
   {
       joystick.y = (float)(joystickY - JOYSTICK_YCTR) / JOYSTICK_UP_MAG * -1.0;
   }
}

void Controls::Update(unsigned long ms_ticks)
{
   float xValue = (JOYSTICK_CTR - (float)analogRead(JOYSTICK_X)) / JOYSTICK_CTR;
   float yValue = (JOYSTICK_CTR - (float)analogRead(JOYSTICK_Y)) / JOYSTICK_CTR;
   joystick.x = ApplyDeadZone(xValue);
   joystick.y = ApplyDeadZone(yValue);
   UpdateJoystick();
   buttons[0] = digitalRead(BTN0);
   buttons[1] = digitalRead(BTN1);
   buttons[2] = digitalRead(BTN2);
   buttons[3] = digitalRead(BTN3);
   buttons[4] = digitalRead(JOY_BTN);
   Serial.println(analogRead(FORWARD_BACK_GYRO));
   //analogRead(FORWARD_BACK_GYRO);
   // Add a new random number to the random number array
   unsigned int cdsVal = analogRead(CDS_CELL);
   if (cdsVal != random_numbers[random_index])
   {
       random_index++;
       if (random_index == NUM_RAND_NUMS)
       {
          random_index = 0;
       }
       random_numbers[random_index] = cdsVal;
   }
}
