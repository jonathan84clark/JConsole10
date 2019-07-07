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
 ****************************************************/
#include "ILI9341_SPI.h"
#include "Sprite.h"
#include "Vector2D.h"
#include <SPI.h>

// For the Adafruit shield, these are the default.
#define TFT_CLK 27
#define TFT_MISO 25
#define TFT_MOSI 26
#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8

// Pins for other subsystems
#define TFT_LED 20
#define SUPER_WHITE_LED 13
#define LEFT_RIGHT_TILT A2
#define FORWARD_BACK_GYRO A1
#define CDS_CELL A3
#define JOYSTICK_X A10
#define JOYSTICK_Y A11
#define BTN0 7
#define BTN1 6
#define BTN2 5
#define BTN3 4
#define JOY_BTN 18

unsigned char testVal = 0;
ILI9341 lcd;
Vector2D newposition(40, 40);
Vector2D vo(3, 12);
Vector2D scale(10, 10);
Sprite testSprite(newposition, scale, &lcd);


void setup() {

  testSprite.velocity = vo;
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

void loop(void) {
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
     Serial.println(testSprite.velocity.y);
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
