/***************************************************
 * JCONSOLE 10
 * DESC: JConsole10 is a hand-held video game system based
 * on the Arduino Due (32-bit) CPU.
 * Date: 6/13/2019
 * Update: 6/17/2019, Finalized the custom ILI9341 driver,
 * validated functionality. Also validated all button functionality.
 * code needs a major refactor before work can begin.
 ****************************************************/
#include "SPI.h"
#include "ILI9341_SPI.h"
#include "ILI9341_Printf.h"
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
TextPrinter textPrinter;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  delay(300);
  ILI9341_begin();
  ILI9341_fillScreen(COLOR_GREENYELLOW);
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
  //printf_drawChar(30, 30, 0, 'A');
  textPrinter._print("Jonaffsdffdthadfsdfsdnsdfsdfz");

  delay(500);

}

unsigned long ms_ticks = 0;
unsigned long next_time = 0;
bool on = false;

void loop(void) {
  ms_ticks = millis();
  if (next_time < ms_ticks)
  {
    Serial.println(analogRead(A11));
    next_time = ms_ticks + 1000;
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
}
