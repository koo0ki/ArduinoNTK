#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

LiquidCrystal_I2C lcd1(0x26, 16, 2);
LiquidCrystal_I2C lcd2(0x27, 16, 2);  
SoftwareSerial mySoftwareSerial(10, 11); 
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  lcd1.init();
  lcd1.backlight();
  lcd2.init();
  lcd2.backlight();
  
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("DFPlayer Mini не удалось инициализировать"));
  }
  
  playSound(2)
}

void loop() {
  // Анимация глаз
  displayEyes();
  
  // Анимация улыбки
  displaySmile();
}

void displayEyes() {
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print("     ##  ##    ");
  lcd1.setCursor(0, 1);
  lcd1.print("     ##  ##    ");
  delay(1000); 
}

void displaySmile() {
  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print("     ____    ");
  lcd2.setCursor(0, 1);
  lcd2.print("   /      \\  ");
  delay(1000); 
  
  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print("     ----    ");
  lcd2.setCursor(0, 1);
  lcd2.print("   \\______/  ");
  delay(1000); 
}

void playSound(int track) {
  if (myDFPlayer.available()) {
    myDFPlayer.play(track);
  }
  
  delay(5000); 
}
