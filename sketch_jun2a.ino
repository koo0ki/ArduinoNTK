#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "CustomCharacters.h" // Импортируем файл с символами
#include "SlotMachine.h"      // Импортируем файл с логикой слотов

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Устанавливаем дисплей

void setup() {
    lcd.init();
    lcd.backlight(); // Включаем подсветку дисплея
    createCustomCharacters(lcd); // Создаем пользовательские символы
    lcd.clear();
}

void loop() {
    runSlotMachine(lcd); // Запускаем анимацию слотов
}
