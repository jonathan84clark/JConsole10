/*******************************************************
* VECTOR 2D CLASS
* DESC: The Vector 2D class is deisnged to provide a simple
* 2 dimensional vector for use in the system.
* Author: Jonathan L Clark
* Date: 7/3/2019
*******************************************************/
#ifndef _VECTOR2D_
#define _VECTOR2D_

#include <stdio.h>
#include <stdint.h>

class Vector2D
{
   public:
      Vector2D();
      
      Vector2D(int inX, int inY);
      float x;
      float y;     
};

#endif
