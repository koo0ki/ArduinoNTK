#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#if (defined(ARDUINO_AVR_UNO) || defined(ESP8266))  // Using a soft serial port
#include <SoftwareSerial.h>
SoftwareSerial softSerial(/*rx =*/10, /*tx =*/11);
#define FPSerial softSerial
#else
#define FPSerial Serial1
#endif

DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

LiquidCrystal_I2C lcd1(0x26, 16, 2);
LiquidCrystal_I2C lcd2(0x27, 16, 2);

void setup() {
#if (defined ESP32)
  FPSerial.begin(9600, SERIAL_8N1, /*rx =*/D3, /*tx =*/D2);
#else
  FPSerial.begin(9600);
#endif

  Serial.begin(115200);
  lcd1.init();
  lcd1.backlight();
  lcd2.init();
  lcd2.backlight();

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(FPSerial, /*isACK = */ true, /*doReset = */ true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true)
      ;
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500);

  myDFPlayer.volume(10);
  myDFPlayer.volumeUp();
  myDFPlayer.volumeDown();

  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);

  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
}

void loop() {
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print("     ##  ##    ");  // Глаза
  lcd1.setCursor(0, 1);
  lcd1.print("     ##  ##    ");  // Глаза
  delay(500);                     // Задержка 1 секунда

  // Выводим улыбку на втором дисплее
  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print("     ____    ");  // Верхняя часть улыбки
  lcd2.setCursor(0, 1);
  lcd2.print("   /      \\  ");  // Рот

  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print("               ");  // Глаза
  lcd1.setCursor(0, 1);
  lcd1.print("     ##  ##    ");  // Глаза
  delay(500);                     // Задержка 1 секунда


  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print("               ");  // Глаза
  lcd1.setCursor(0, 1);
  lcd1.print("     __  __    ");  // Глаза
  delay(500);

  // Меняем улыбку на втором дисплее
  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print("     ----    ");  // Верхняя часть улыбки
  lcd2.setCursor(0, 1);
  lcd2.print("   \\______/  ");  // Рот
  delay(500);

  
}

void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
