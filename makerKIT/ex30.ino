#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// if the liquid crystal import gves you a not found error
// download it here https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
void setup()
{
    lcd.init(); // initialize the lcd
    lcd.init();
    // Print a message to the LCD.
    lcd.backlight();
    lcd.setCursor(3,0);
    lcd.print("dad");
    lcd.setCursor(2,1);
    lcd.print("is a crab");
}
void loop()
{
}