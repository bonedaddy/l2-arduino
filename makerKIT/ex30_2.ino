#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// if the liquid crystal import gves you a not found error
// download it here https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
char row1[16] = {'r', 'h', 'i', 'a', 'n', 'n', 'o', 'n', ' ', 'a', ' ', 't', 'h', 'i', 'c', 'c'};
char row2[5] = {'h', 'o', 't', 't', 'y'};
void setup()
{
    lcd.init(); // initialize the lcd
    lcd.backlight();
}
void loop()
{
    for (int i=0; i<16; i++) {
        lcd.setCursor(i, 0);
        lcd.write(row1[i]);
        delay(10);
    }
    for (int i=0; i<5; i++) {
        lcd.setCursor(i, 1);
        lcd.write(row2[i]);
        delay(10);
    }
}