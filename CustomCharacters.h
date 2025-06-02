// CustomCharacters.h

#ifndef CustomCharacters_h
#define CustomCharacters_h

#include <LiquidCrystal_I2C.h>

// Определяем символы
byte apple[8] = {
    0b00100,
    0b01110,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000,
    0b00000
};

byte banana[8] = {
    0b00010,
    0b00110,
    0b01100,
    0b01000,
    0b01100,
    0b00110,
    0b00010,
    0b00000
};

byte cherry[8] = {
    0b00100,
    0b01110,
    0b11111,
    0b11111,
    0b00100,
    0b00000,
    0b00000,
    0b00000
};

byte orange[8] = {
    0b00100,
    0b01110,
    0b01010,
    0b01010,
    0b01110,
    0b00100,
    0b00000,
    0b00000
};

byte grape[8] = {
    0b00100,
    0b01110,
    0b11110,
    0b11111,
    0b01110,
    0b00100,
    0b00000,
    0b00000
};

// Массив символов
byte* fruits[] = { apple, banana, cherry, orange, grape };
const int fruitCount = sizeof(fruits) / sizeof(fruits[0]);

void createCustomCharacters(LiquidCrystal_I2C &lcd) {
    for (int i = 0; i < fruitCount; i++) {
        lcd.createChar(i, fruits[i]);
    }
}

#endif
