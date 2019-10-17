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
#define MAX_ADC 1024
#define MIN_ADC 0

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
  random_pull_indx = 0;
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(CDS_CELL, INPUT);
  pinMode(BTN0, INPUT);
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BTN3, INPUT);
  pinMode(LEFT_RIGHT_TILT, INPUT);
  pinMode(FORWARD_BACK_GYRO, INPUT);
  pinMode(JOY_BTN, INPUT);


}

void Controls::Setup()
{
   joystick_ctr_x = analogRead(JOYSTICK_X);
   joystick_ctr_y = analogRead(JOYSTICK_Y);
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

/**************************************************
* RANDOM
* DESCRIPTION: Generates a random number between 0-1024.
**************************************************/
unsigned int Controls::Random(unsigned int max)
{
    unsigned int value = random_numbers[random_pull_indx] % max;
    random_pull_indx++;
    if (random_pull_indx == NUM_RAND_NUMS)
    {
       random_pull_indx = 0;
    }
    return value;
}

/**************************************************
* UPDATE
* DESCRIPTION: Updates the controls with the latest
* control information.
**************************************************/
void Controls::Update(unsigned long ms_ticks)
{
   float xValue = (joystick_ctr_x - (float)analogRead(JOYSTICK_X)) / joystick_ctr_x;
   float yValue = (joystick_ctr_y - (float)analogRead(JOYSTICK_Y)) / joystick_ctr_y;

   joystick.x = ApplyDeadZone(xValue);
   joystick.y = ApplyDeadZone(yValue);
   buttons[0] = digitalRead(BTN0);
   buttons[1] = digitalRead(BTN1);
   buttons[2] = digitalRead(BTN2);
   buttons[3] = digitalRead(BTN3);
   buttons[4] = digitalRead(JOY_BTN);
   // Add a new random number to the random number array
   unsigned int randomValue = analogRead(CDS_CELL) + analogRead(LEFT_RIGHT_TILT) + analogRead(FORWARD_BACK_GYRO) + ms_ticks;
   if (randomValue != random_numbers[random_index])
   {
       random_index++;
       if (random_index == NUM_RAND_NUMS)
       {
          random_index = 0;
       }
       random_numbers[random_index] = randomValue;
   }
}
