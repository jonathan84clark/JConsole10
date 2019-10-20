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
 * Update: 10/16/2019, Fixed a minor issue with the controls. Also added computations to make a better
 * random number generator.
 * Update: 10/18/2019, Added support for a vertacle UI bar. 
 * Update: 10/19/2019, Added code to support a sprite image. Added the resistance x-wing sprite object
 * now the player can play the game with an x-wing.
 ****************************************************/
#include "src/hal/ILI9341_SPI.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "src/hal/Controls.h"
#include "UIBar.h"
#include <SPI.h>

// Pins for other subsystems
#define TFT_LED 20
#define SUPER_WHITE_LED 13

#define NUM_BLOCKS 10
#define NUM_SHOTS 10


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

int testSprite[] = {COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,
                    COLOR_BLUE, COLOR_BLUE, COLOR_BLUE, COLOR_BLUE,
                    COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED};

#define SIZE_X 7
#define SIZE_Y 6
int twoDArrayTest[] = {COLOR_BLUE, COLOR_BLUE, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,
                                     COLOR_BLUE, COLOR_BLUE, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,
                                     COLOR_BLUE, COLOR_BLUE, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,
                                     COLOR_BLUE, COLOR_BLUE, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,
                                     COLOR_BLUE, COLOR_BLUE, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,
                                     COLOR_BLUE, COLOR_BLUE, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED};

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

void setup() {


  delay(3000);
  Serial.begin(9600);
  SPI.begin();

  controls.Setup();
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
   Sprite shots[NUM_SHOTS];
   Sprite blocks[NUM_BLOCKS];
   UIBar health(newposition, true, 4, 40, COLOR_BLUE, COLOR_RED, &lcd);
   health.update(0.8);
   int shotIndex = 0;
   int block_create_index = 0;
   Vector2D newposition(200, 50);
   Vector2D newVelocity(0,0);
   Vector2D playerScale(XWING_WIDTH, XWING_HEIGHT);
   player = Sprite(newposition, playerScale, 0.0, 0.0, 0, false, 12, xWing, &lcd);
   vo = Vector2D(3.0, 3.0);
   newposition = Vector2D(140, 50);
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
            shots[shotIndex] = Sprite(player.GetPosition(), blasterScaler, 0.8, 0.0, 0, true, 12, 0, &lcd);
            Vector2D shotVel = Vector2D(5.0, 0.0);
            shotVel.x += player.GetVelocity().x;
            shotVel.y += player.GetVelocity().y;
            shots[shotIndex++].SetVelocity(shotVel);
            if (shotIndex == NUM_SHOTS)
            {
               shotIndex = 0;
            }
         }
         next_time = ms_ticks + 200;
      }
      if (next_block_time < ms_ticks)
      {
          startBlockPos.y = controls.Random(300);
          for (int i = 0; i < NUM_SHOTS; i++)
          {
            if (!blocks[i].GetIsAlive())
            {
               blocks[i] = Sprite(startBlockPos, scale, 0.0, 0.0, 0, true, 12, 0, &lcd);
               Vector2D newVel = Vector2D(-5.0, 0.0);
               blocks[i].SetVelocity(newVel);
               break;
            }
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
                  }
               }
            }
         }
         for (int i = 0; i < NUM_BLOCKS; i++)
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
  //ms_ticks = millis();
}
