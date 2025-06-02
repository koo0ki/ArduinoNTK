// SlotMachine.h

#ifndef SlotMachine_h
#define SlotMachine_h

#include <LiquidCrystal_I2C.h>

void runSlotMachine(LiquidCrystal_I2C &lcd) {
    // Крутящаяся анимация слотов
    for (int spin = 0; spin < 20; spin++) { // 20 "крутов"
        lcd.clear();

        for (int col = 0; col < 3; col++) { // Три колонки
            int fruitIndex = random(5); // Случайный индекс фрукта
            lcd.setCursor(col * 5, 0); // Устанавливаем курсор для первой строки
            lcd.write((byte)fruitIndex); // Выводим фрукт
        }

        delay(100); // Задержка между крутками
    }

    // Отображение результата
    lcd.clear();
    for (int col = 0; col < 3; col++) { // Три колонки
        int fruitIndex = random(5); // Случайный индекс для финального показа
        lcd.setCursor(col * 5, 0); // Устанавливаем курсор для первой строки
        lcd.write((byte)fruitIndex); // Выводим фрукт
    }

    delay(3000); // Задержка, чтобы показать результат
}

#endif
