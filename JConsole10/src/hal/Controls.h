/*******************************************************
* CONTROLS
* DESC: The controls class provides an interface to the
* various controls of JConsole10. Internally it handles
* all button debouncing and system state collections.
* Author: Jonathan L Clark
* Date: 7/16/2019
*******************************************************/
#ifndef _CONTROLS_
#define _CONTROLS_

#include "../../Vector2D.h"

#define NUM_RAND_NUMS 15

class Controls
{
   public:
      Controls();
      void Update(unsigned long ms_ticks);
      Vector2D joystick;
      Vector2D gyro;
      bool buttons[5];
      unsigned int random_numbers[NUM_RAND_NUMS];
      unsigned int random_index;
      unsigned int Random(unsigned int max);
      void Setup();

   private:
     int joystick_ctr_x;
     int joystick_ctr_y;
     int random_pull_indx;
     float ApplyDeadZone(float inValue);  
};

#endif
