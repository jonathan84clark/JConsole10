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
 ****************************************************/
#include "ILI9341_SPI.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "Controls.h"
#include <SPI.h>

// Pins for other subsystems
#define TFT_LED 20
#define SUPER_WHITE_LED 13
#define LEFT_RIGHT_TILT A2
#define FORWARD_BACK_GYRO A1
#define CDS_CELL A3
#define BTN0 7
#define BTN1 6
#define BTN2 5
#define BTN3 4
#define JOY_BTN 18

unsigned char testVal = 0;
ILI9341 lcd;
Vector2D newposition(200, 50);
Vector2D sprite2Pos(0, 50);
Vector2D vo(-3.0, 0.0);
Vector2D scale(10, 10);
Vector2D scale2(10, 10);
Vector2D blasterScaler(10, 3);
Sprite testSprite(newposition, scale, 0.4, 0.01, 0, false, &lcd);
Sprite testSprite2(sprite2Pos, scale2, 0.4, 0.01, 0, false, &lcd);
Controls controls;

void setup() {

  testSprite.SetVelocity(vo);
  testSprite = Sprite(newposition, scale2, 0.4, 0.1, 0, false, &lcd);
  testSprite.SetVelocity(vo);
  delay(1500);
  Serial.begin(9600);
  SPI.begin();

  lcd.initialize();
  lcd.fillScreen(COLOR_GREENYELLOW);
  Serial.println("ILI9341 Test!"); 
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);
  pinMode(SUPER_WHITE_LED, OUTPUT);
  digitalWrite(SUPER_WHITE_LED, LOW);
  pinMode(BTN0, INPUT);
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BTN3, INPUT);
  pinMode(JOY_BTN, INPUT);
  delay(300);
  
  //testSprite.draw();
  //testSprite2.draw();
  testSprite.draw();
  //lcd._print("Jonaffsdffdthadfsdfsdnsdfsdfz");

  delay(500);

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
   int shotIndex = 0;
   //Sprite sprites[10];
   Vector2D newposition(200, 50);
   Vector2D newVelocity(0,0);
   player = Sprite(newposition, scale2, 0.8, 0.0, 0, false, &lcd);
   //sprites[0] = Sprite(newposition, scale2, 0.8, 0.0, 0, false, &lcd);
   //sprites[0].SetVelocity(vo);
   vo = Vector2D(3.0, 3.0);
   newposition = Vector2D(140, 50);
   
   //sprites[1] = Sprite(newposition, scale2, 0.8, 0.0, 0, false, &lcd);
   //sprites[1].SetVelocity(vo);
   unsigned long next_player = 0;
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
         if (digitalRead(BTN0))
         {
            shots[shotIndex] = Sprite(player.GetPosition(), blasterScaler, 0.8, 0.0, 0, false, &lcd);

            Vector2D shotVel = Vector2D(5.0, 0.0);
            shots[shotIndex++].SetVelocity(shotVel);
            if (shotIndex == 10)
            {
               shotIndex = 0;
            }
         }
         next_time = ms_ticks + 200;
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
            for (int j = 0; j < 10; j++)
            {
                //if (j != i && sprites[i].GetIsAlive())
                //{
                //   sprites[i].check_collision(&sprites[j]);
                //}
            }
         }
         
         //Serial.println(controls.joystick.x);
         //testSprite.update(delta_time_sec);
         next_update = ms_ticks + 40;
         last_time = ms_ticks;
      }
   }
}

void loop(void) {
  testGame();
  ms_ticks = millis();
  delta_time = ms_ticks - last_time;
  if (next_time < ms_ticks)
  {
    //Serial.println(analogRead(A11));
    next_time = ms_ticks + 1000;
  }
  if (next_update < ms_ticks)
  {
     delta_time = ms_ticks - last_time;
     delta_time_sec = (float)delta_time;
     delta_time_sec = delta_time_sec / 1000.0;
     //testSprite.update();
     //testSprite.move_sprite(movement);
     //Serial.println(delta_time_sec);
     testSprite.update(delta_time_sec);
     //testSprite.check_collision(&testSprite2);
     //Serial.println(testSprite.velocity.y);
     next_update = ms_ticks + 40;
     last_time = ms_ticks;
  }
  if (digitalRead(BTN0))
  {
    Serial.println("Button0");
  }
  if (digitalRead(BTN1))
  {
    Serial.println("Button1");
  }
  if (digitalRead(BTN2))
  {
    Serial.println("Button2");
  }
  if (digitalRead(BTN3))
  {
    Serial.println("Button3");
  }
  if (digitalRead(JOY_BTN))
  {
    Serial.println("Joystick Btn");
  }
  //last_time = ms_ticks;
}
