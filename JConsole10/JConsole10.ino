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
 * Update: 10/21/2019, Pulled off the Debris game into it's own header and .cpp files for organization.
 * Update: 10/21/2019, Made signficant changes. Added sprite orientation, added the blaster class
 * cleaned up the game code and added comments, added a health bar and health to the game. Added multiple
 * weapon shots. Adjusted the speed of the player's weapon.
 ****************************************************/
#include "src/hal/ILI9341_SPI.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "src/hal/Controls.h"
#include "Debris.h"
#include <SPI.h>

// Pins for other subsystems
#define TFT_LED 20
#define SUPER_WHITE_LED 13

ILI9341 lcd;
Controls controls;


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
  debris(&lcd, &controls);
}


void loop(void) {
   // Do nothing, game menus and sub-games are contained within other functions
}
