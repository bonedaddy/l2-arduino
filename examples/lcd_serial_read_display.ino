#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// if the liquid crystal import gves you a not found error
// download it here https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display
void setup()
{
    lcd.init(); // initialize the lcd
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("type stuff");
    Serial.begin(9600);
}
void loop()
{
  // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      lcd.write(Serial.read());
    }
  }
}