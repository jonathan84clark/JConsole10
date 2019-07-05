/*******************************************************
* VECTOR 2D CLASS
* DESC: The Vector 2D class is deisnged to provide a simple
* 2 dimensional vector for use in the system.
* Author: Jonathan L Clark
* Date: 7/3/2019
*******************************************************/

#include "Vector2D.h"

/*******************************************
* VECTOR 2D Default constructor
*******************************************/
Vector2D::Vector2D()
{
  x = 0;
  y = 0;
}

/*******************************************
* VECTOR 2D Constructor
*******************************************/
Vector2D::Vector2D(int inX, int inY)
{
   x = inX;
   y = inY;
}
