#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// if the liquid crystal import gves you a not found error
// download it here https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
byte smile[8] = 

              {

                0b00000,

                0b00000,

                0b01010,

                0b00000,

                0b10001,

                0b01110,

                0b00000,

                0b00000

              };
void setup()
{
    lcd.createChar(0, smile);
    lcd.init(); // initialize the lcd
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Shroomery is");
    lcd.setCursor(0, 1);
    lcd.print("AWESOME");
    lcd.write(byte(0));
}
void loop()
{
}