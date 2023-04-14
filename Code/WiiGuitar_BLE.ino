#include <Arduino.h>
#include <BleGamepad.h>
#include <Wire.h>

//#define DEBUG

#define WIIGUITAR_ADDRESS 0x52

static void WiiGuitar_Init();
static uint8_t WiiGuitar_Read();

uint8_t wg_data[6];
BleGamepad bleGamepad;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Setup Start");
  bleGamepad.begin();
  Serial.println("Gamepad Start");
  Wire.begin();
  Serial.println("I2C Start");
  WiiGuitar_Init();
  Serial.println("Guitar Start");
  Serial.println("Setup Complete");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Loop Start");
  if (bleGamepad.isConnected()) {
    Serial.println("BLE Connected");
    if (WiiGuitar_Read()) {
       Serial.println("Guitar Read");
      if ((~wg_data[4] >> 2) & 1) {    //B+
        Serial.print("B+, ");
        bleGamepad.press(BUTTON_1);
      } else {
        bleGamepad.release(BUTTON_1);
      }
      
      if ((~wg_data[4] >> 4) & 1) {    //B-
        Serial.print("B-, ");
        bleGamepad.press(BUTTON_2);
      } else {
        bleGamepad.release(BUTTON_2);
      }
      
      if ((~wg_data[4] >> 6) & 1) {    //BD
        Serial.print("SD, ");
        bleGamepad.press(BUTTON_3);
      } else {
        bleGamepad.release(BUTTON_3);
      }
      
      if ((~wg_data[5] >> 0) & 1) {    //BU
        Serial.print("SU, ");
        bleGamepad.press(BUTTON_4);
      } else {
        bleGamepad.release(BUTTON_4);
      }
      
      if ((~wg_data[5] >> 3) & 1) {    //BY
        Serial.print("BY, ");
        bleGamepad.press(BUTTON_5);
      } else {
        bleGamepad.release(BUTTON_5);
      }
      
      if ((~wg_data[5] >> 4) & 1) {    //BG
        Serial.print("BG, ");
        bleGamepad.press(BUTTON_6);
      } else {
        bleGamepad.release(BUTTON_6);
      }
      
      if ((~wg_data[5] >> 5) & 1) {    //BB
        Serial.print("BB, ");
        bleGamepad.press(BUTTON_7);
      } else {
        bleGamepad.release(BUTTON_7);
      }
      
      if ((~wg_data[5] >> 6) & 1) {    //BR
        Serial.print("BR, ");
        bleGamepad.press(BUTTON_8);
      } else {
        bleGamepad.release(BUTTON_8);
      }
      
      if ((~wg_data[5] >> 7) & 1) {    //BO
        Serial.print("BO, ");
        bleGamepad.press(BUTTON_9);
      } else {
        bleGamepad.release(BUTTON_9);
      }
      Serial.print("\n");
    }
  } else {
    Serial.println("BLE not connectred");
  }
  Serial.println("Loop End\n");
}

static void WiiGuitar_Init() {
  Wire.beginTransmission(WIIGUITAR_ADDRESS);
  Wire.write(0xF0);
  Wire.write(0x55);
  Wire.endTransmission(true);
  // delay(1);
  Wire.beginTransmission(WIIGUITAR_ADDRESS);
  Wire.write(0xFB);
  Wire.write(0x00);
  Wire.endTransmission(true);
  //delay(1)
}

static uint8_t WiiGuitar_Read() {
  uint8_t i;
  Wire.requestFrom(WIIGUITAR_ADDRESS, 6);
  for (i = 0; i < 6 && Wire.available(); i++) {
      wg_data[i] = Wire.read();
  }
  Wire.beginTransmission(WIIGUITAR_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission(true);
  return i == 6;
}
