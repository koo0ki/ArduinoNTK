#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Инициализация дисплеев
LiquidCrystal_I2C lcd1(0x26, 16, 2);  // Первый дисплей (глаза)
LiquidCrystal_I2C lcd2(0x27, 16, 2);  // Второй дисплей (улыбка)

void setup() {
  lcd1.init();
  lcd1.backlight();  // Включаем подсветку первого дисплея
  lcd2.init();
  lcd2.backlight();  // Включаем подсветку второго дисплея
}

void loop() {
  // Выводим глаза на первом дисплее
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
  delay(500);                    // Задержка 1 секунда
}
