/***************************************************
 * JCONSOLE 10
 * DESC: JConsole10 is a hand-held video game system based
 * on the Arduino Due (32-bit) CPU.
 * Date: 6/13/2019
 * Update: 6/17/2019, Finalized the custom ILI9341 driver,
 * validated functionality. Also validated all button functionality.
 * code needs a major refactor before work can begin.
 * Update: 7/2/2019, Encapsulated the an ILI9341 driver into a class for the LCD.
 * added the sprite class to the game.
 * Update: 7/4/2019, Added basic vector movement of objects in the game.
 * Update: 7/5/2019, Added some basic physics to the game.
 * Update: 7/6/2019, Fixed some issues with the physics system. Continued work on the sprite object.
 * Update: 7/11/2019, Improved the physics engine. Finished colliders.
 * Update: 10/10/2019, Added player control code. Modified the controls driver to use scalers. 
 * added basic shooting effects to the game.
 * Update: 7/17/2019, Started putting together the control system.
 * Update; 10/12/2019, Added code to support setting the color of Sprites. Cleaned up the code. Added
 * code to start generating blocks. Continuing to flesh out the drivers.
 ****************************************************/
#include "ILI9341_SPI.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "Controls.h"
#include <SPI.h>

// Pins for other subsystems
#define TFT_LED 20
#define SUPER_WHITE_LED 13


unsigned char testVal = 0;
ILI9341 lcd;
Vector2D newposition(200, 50);
Vector2D startBlockPos(300, 50);
Vector2D sprite2Pos(0, 50);
Vector2D vo(-3.0, 0.0);
Vector2D scale(10, 10);
Vector2D scale2(10, 10);
Vector2D blasterScaler(10, 3);
Controls controls;

void setup() {

  delay(3000);
  Serial.begin(9600);
  SPI.begin();

  lcd.initialize();
  lcd.setBgColor(COLOR_GREENYELLOW);
  Serial.println("ILI9341 Test!"); 
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);
  pinMode(SUPER_WHITE_LED, OUTPUT);
  digitalWrite(SUPER_WHITE_LED, LOW);

}

unsigned long ms_ticks = 0;
unsigned long next_time = 0;
unsigned long next_update = 0;
bool on = false;
unsigned long last_time = 0;
unsigned long delta_time = 0;
float delta_time_sec;

void testGame()
{
   Vector2D vo(-3.0, 3.0);
   Sprite player;
   Sprite shots[10];
   Sprite blocks[10];
   int shotIndex = 0;
   int block_create_index = 0;
   //Sprite sprites[10];
   Vector2D newposition(200, 50);
   Vector2D newVelocity(0,0);
   player = Sprite(newposition, scale2, 0.8, 0.0, 0, false, 12, &lcd);
   //sprites[0] = Sprite(newposition, scale2, 0.8, 0.0, 0, false, &lcd);
   //sprites[0].SetVelocity(vo);
   vo = Vector2D(3.0, 3.0);
   newposition = Vector2D(140, 50);
   
   //sprites[1] = Sprite(newposition, scale2, 0.8, 0.0, 0, false, &lcd);
   //sprites[1].SetVelocity(vo);
   unsigned long next_player = 0;
   unsigned long next_block_time = 0;
   for (;;)
   {
      ms_ticks = millis();
      delta_time = ms_ticks - last_time;
      if (next_time < ms_ticks)
      {
         controls.Update(ms_ticks);
         newVelocity.x = controls.joystick.x * 8.0;
         newVelocity.y = controls.joystick.y * 8.0;
         player.SetVelocity(newVelocity);
         if (controls.buttons[0])
         {
            shots[shotIndex] = Sprite(player.GetPosition(), blasterScaler, 0.8, 0.0, 0, true, 12, &lcd);
            Vector2D shotVel = Vector2D(5.0, 0.0);
            shotVel.x += player.GetVelocity().x;
            shotVel.y += player.GetVelocity().y;
            shots[shotIndex++].SetVelocity(shotVel);
            if (shotIndex == 10)
            {
               shotIndex = 0;
            }
         }
         next_time = ms_ticks + 200;
      }
      if (next_block_time < ms_ticks)
      {
          blocks[block_create_index] = Sprite(startBlockPos, scale, 0.0, 0.0, 0, true, 12, &lcd);
          Vector2D newVel = Vector2D(-5.0, 0.0);
          blocks[block_create_index++].SetVelocity(newVel);
          if (block_create_index == 10)
          {
              block_create_index = 0;
          }
          next_block_time = ms_ticks + 203;
      }
      if (next_player < ms_ticks)
      {
         
         next_player = ms_ticks + 203;
      }
      if (next_update < ms_ticks)
      {
         delta_time = ms_ticks - last_time;
         delta_time_sec = (float)delta_time;
         delta_time_sec = delta_time_sec / 1000.0;
         player.update(delta_time_sec);
         //shot.update(delta_time_sec);
         for (int i = 0; i < 10; i++)
         {
            if (shots[i].GetIsAlive())
            {
               shots[i].update(delta_time_sec);
            }
         }
         for (int i = 0; i < 10; i++)
         {
            if (blocks[i].GetIsAlive())
            {
               blocks[i].update(delta_time_sec);
            }
         }
         //testSprite.update(delta_time_sec);
         next_update = ms_ticks + 40;
         last_time = ms_ticks;
      }
   }
}

void loop(void) {
  testGame();
  ms_ticks = millis();
}
