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

#include "Vector2D.h"



class Controls
{
   public:
      Controls();
      void Update(unsigned long ms_ticks);
      Vector2D joystick;




   private:
     


  
};

#endif
