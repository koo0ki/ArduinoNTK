#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#include <WS2812FX.h>
#include <SoftwareSerial.h>

#define LED_COUNT 16
#define LED_PIN 6
#define TIMER_MS 3000
#define btn 2

SoftwareSerial softSerial(/*rx =*/10, /*tx =*/11);
#define FPSerial softSerial

DFRobotDFPlayerMini myDFPlayer;
WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

void printDetail(uint8_t type, int value);

LiquidCrystal_I2C lcd1(0x26, 16, 2);
LiquidCrystal_I2C lcd2(0x27, 16, 2);


unsigned long last_change = 0;
unsigned long now = 0;

byte last = 0;

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

  if (!myDFPlayer.begin(FPSerial, true, true)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true)
      ;
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500);

  myDFPlayer.volume(25);

  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);

  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  ws2812fx.init();
  ws2812fx.setBrightness(30);
  ws2812fx.setSpeed(1000);
  ws2812fx.setColor(0x007BFF);
  ws2812fx.setMode(FX_MODE_STATIC);
  ws2812fx.start();

  pinMode(btn, INPUT_PULLUP);
}

void loop() {

  now = millis();

  ws2812fx.service();

  if (now - last_change > TIMER_MS) {
    ws2812fx.setMode((ws2812fx.getMode() + 4));
    last_change = now;
  }

  byte btn_sig = !digitalRead(btn);

  if (btn_sig != last && btn_sig) {
    myDFPlayer.next();
  }

  last = btn_sig;

  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print("     ##  ##    ");
  lcd1.setCursor(0, 1);
  lcd1.print("     ##  ##    ");
  delay(500);

  lcd2.clear();
  lcd2.setCursor(0, 1);
  lcd2.print("    ______  ");

  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print("               ");
  lcd1.setCursor(0, 1);
  lcd1.print("     ##  ##    ");
  delay(500);


  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print("     __  __    ");
  lcd1.setCursor(0, 1);
  lcd1.print("               ");

  delay(500);

  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd2.print("   |______/  ");
  lcd2.setCursor(0, 1);
  lcd2.print("    ______   ");
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
