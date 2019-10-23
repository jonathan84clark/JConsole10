/*******************************************************
* DEBRIS
* DESC: Debris is the first JConsole game ever invented and
* the first one ported to JConsole10.
* Author: Jonathan L Clark
* Date: 10/21/2019
*******************************************************/
#include <stdio.h>
#include <Arduino.h>
#include "src/hal/ILI9341_SPI.h"
#include "src/hal/Controls.h"
#include "Debris.h"
#include "Sprite.h"
#include "Blaster.h"
#include "UIBar.h"
#include "Vector2D.h"


#define NUM_BLOCKS 10
#define NUM_SHOTS 10

// Static image for the xWing
#define XWING_WIDTH 21
#define XWING_HEIGHT 24

static int xWing[] = {
COLOR_WHITE, COLOR_WHITE,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_WHITE, COLOR_WHITE,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK, COLOR_BLACK, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_BLACK,  COLOR_BLACK,  COLOR_ORANGE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_BLACK,  COLOR_BLACK,  COLOR_ORANGE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_BLACK,  COLOR_BLACK,  COLOR_ORANGE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_BLACK,  COLOR_BLACK,  COLOR_ORANGE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_WHITE,  COLOR_BLACK,  COLOR_BLACK,  COLOR_ORANGE, COLOR_WHITE,  COLOR_BLACK, COLOR_BLACK,  COLOR_ORANGE, COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_WHITE,  COLOR_BLACK,  COLOR_BLACK,  COLOR_ORANGE, COLOR_WHITE,  COLOR_BLACK, COLOR_BLACK,  COLOR_ORANGE, COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_GREY,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK, COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_GREY,  COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_GREY,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK, COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_GREY,  COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK, COLOR_BLACK,  COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK, COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK, COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK, COLOR_BLACK,  COLOR_BLUE,   COLOR_BLUE,   COLOR_BLUE,  COLOR_BLUE,  COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_ORANGE, COLOR_ORANGE, COLOR_BLACK, COLOR_BLACK,
COLOR_WHITE, COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK, COLOR_BLACK,  COLOR_BLUE,   COLOR_BLUE,   COLOR_BLUE,  COLOR_BLUE,  COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_ORANGE, COLOR_ORANGE, COLOR_BLACK, COLOR_BLACK,
COLOR_WHITE, COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK, COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK, COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK, COLOR_BLACK,  COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_GREY,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK, COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_GREY,  COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_GREY,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK, COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_GREY,  COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_WHITE,  COLOR_BLACK,  COLOR_BLACK,  COLOR_ORANGE, COLOR_WHITE,  COLOR_BLACK, COLOR_BLACK,  COLOR_ORANGE, COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_WHITE,  COLOR_BLACK,  COLOR_BLACK,  COLOR_ORANGE, COLOR_WHITE,  COLOR_BLACK, COLOR_BLACK,  COLOR_ORANGE, COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_BLACK,  COLOR_BLACK,  COLOR_ORANGE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_BLACK,  COLOR_BLACK,  COLOR_ORANGE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_BLACK,  COLOR_BLACK,  COLOR_ORANGE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_BLACK,  COLOR_BLACK,  COLOR_ORANGE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
COLOR_WHITE, COLOR_WHITE,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK,  COLOR_WHITE, COLOR_WHITE,  COLOR_BLACK,  COLOR_BLACK,  COLOR_BLACK, COLOR_BLACK, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE,  COLOR_WHITE,  COLOR_WHITE, COLOR_WHITE,
};

#define RATE_OF_FIRE 100
//UIBar health(newposition, true, 4, 40, COLOR_BLUE, COLOR_RED, &lcd);
//health.update(0.8);

/********************************************************
* DEBRIS
* DESC: Contains the debris game, where the player can shoot
* block objects.
********************************************************/
void debris(ILI9341 *lcd, Controls *controls)
{
   unsigned long ms_ticks = 0;
   unsigned long player_timer = 0;
   unsigned long last_time = 0;
   unsigned long update_timer = 0;
   unsigned long block_gen_timer = 0;
   unsigned long shot_rof_timer = 0;
   unsigned long score = 0;
   float health = 100.0;
   float max_health = health;
   Vector2D startBlockPos(300, 50);
   Sprite player;
   Blaster shots[NUM_SHOTS];
   Sprite blocks[NUM_BLOCKS];
   int shotIndex = 0;
   int shotStartLoc = 0;
   player = Sprite(Vector2D(100, 75), Vector2D(XWING_WIDTH, XWING_HEIGHT), 0.0, 0.0, 0, false, 12, xWing, lcd);
   float delta_time;
   lcd->SetCursor(230, 230);
   lcd->_print("Health");
   UIBar healthBar(Vector2D(230, 210), false, 6, 70, COLOR_BLUE, COLOR_RED, lcd);
   healthBar.update(1.0);
   lcd->SetCursor(5, 230);
   String value = String(0);
   lcd->_print("Score: ");
   lcd->SetCursor(85, 230);
   lcd->_print(value);
   
   for (;;)
   {
      ms_ticks = millis();
      controls->UpdateButtons();
      if (player_timer < ms_ticks)
      {
         controls->Update(ms_ticks);
         player.SetVelocity(Vector2D(controls->joystick.x * 8.0, controls->joystick.y * 8.0));
         player_timer = ms_ticks + 200;
      }
      // Fire Button Pressed
      if (shot_rof_timer < ms_ticks && controls->buttons[3])
      {
         // Circular queue here, its possible to run out of shots
         if (!shots[shotIndex].GetIsAlive())
         {
            Vector2D shotStart = player.GetPosition();
            shotStart.x += 3;
            if (shotStartLoc == 1)
            {
               shotStart.y += player.GetScale().y;
            }
            shots[shotIndex] = Blaster(shotStart, COLOR_RED, lcd);
            if (player.GetOrientation() == 3)
            {
               shots[shotIndex++].SetVelocity(Vector2D(-10.0 + player.GetVelocity().x, 0.0));
            }
            else
            {
               shots[shotIndex++].SetVelocity(Vector2D(10.0 + player.GetVelocity().x, 0.0));
            }
            if (shotIndex == NUM_SHOTS)
            {
               shotIndex = 0;
            }
            shotStartLoc++;
            if (shotStartLoc == 2)
            {
               shotStartLoc = 0;
            }
            shot_rof_timer = ms_ticks + RATE_OF_FIRE;
         }
      }
      // Auto Generate blocks when they are destroyed
      if (block_gen_timer < ms_ticks)
      {
          controls->Update(ms_ticks);
          startBlockPos.y = controls->Random(300);
          if (startBlockPos.y > 180)
          {
              startBlockPos.y = controls->Random(300);
              if (startBlockPos.y > 180.0)
              {
                 startBlockPos.y = 180;
              }
          }
          for (int i = 0; i < NUM_BLOCKS; i++)
          {
            if (!blocks[i].GetIsAlive())
            {
               blocks[i] = Sprite(startBlockPos, Vector2D(10, 10), 0.0, 0.0, 0, true, 12, 0, lcd);
               blocks[i].SetVelocity(Vector2D(-5.0, 0.0));
               break;
            }
          }
          block_gen_timer = ms_ticks + 203;
      }
      // Updates all the gameobjects in the game, moving them and
      // checking for collisions.
      if (update_timer < ms_ticks)
      {
         delta_time = ms_ticks - last_time;
         float delta_time_sec = (float)delta_time;
         delta_time_sec = delta_time_sec / 1000.0;
         player.update(delta_time_sec);
         // Update all shots
         for (int i = 0; i < NUM_SHOTS; i++)
         {
            if (shots[i].GetIsAlive())
            {
               shots[i].update(delta_time_sec);
               for (int j = 0; j < NUM_BLOCKS; j++)
               {
                  if (blocks[j].GetIsAlive() && blocks[j].check_collision(&shots[i]))
                  {
                      blocks[j].destroy();
                      shots[i].destroy();
                      score++;
                      String value = String(score);
                      lcd->SetCursor(85, 230);
                      lcd->_print(value);
                  }
               }
            }
         }
         // Update all blocks
         for (int i = 0; i < NUM_BLOCKS; i++)
         {
            if (blocks[i].GetIsAlive())
            {
               blocks[i].update(delta_time_sec);
               if (blocks[i].check_collision(&player))
               {
                   // Reduce the player's health or/and destroy the player object
                   if (health > 0.0)
                   {
                      health--;
                      healthBar.update(health/max_health);
                      // TODO: Handle restarting the game
                   }
                   blocks[i].destroy();
                   player.draw(); // Redraw the player
               }
            }
         }
         update_timer = ms_ticks + 40;
      }
      last_time = ms_ticks; // Store the last tick to get delta time
   }
}
