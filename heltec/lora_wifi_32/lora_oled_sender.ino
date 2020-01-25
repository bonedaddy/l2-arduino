/*
  This is a simple example show the Heltec.LoRa sended data in OLED.
  The onboard OLED display is SSD1306 driver and I2C interface. In order to make the
  OLED correctly operation, you should output a high-low-high(1-0-1) signal by soft-
  ware to OLED's reset pin, the low-level signal at least 5ms.
  OLED pins to ESP32 GPIOs via this connecthin:
  OLED_SDA -- GPIO4
  OLED_SCL -- GPIO15
  OLED_RST -- GPIO16
  
  by Aaron.Lee from HelTec AutoMation, ChengDu, China
  成都惠利特自动化科技有限公司
  https://heltec.org
  
  this project also realess in GitHub:
  https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series
*/
#include "heltec.h"

#define logo_width 128
#define logo_height 53
#define BAND    868E6  //you can set band here directly,e.g. 868E6,915E6

const unsigned char logo_bits[] = {
   
  0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x01, 0xF0, 0x03, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xC0, 0x07, 0xF0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xC0, 0x0F, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x1F, 0xF0, 0x1F, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xE0, 0x1F, 0xF0, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xE0, 0x3F, 0xF8, 0x3F, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x1F, 0xF8, 0x3F, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xE0, 0x1F, 0xF8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xF0, 0x1F, 0xF8, 0x1F, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x1F, 0xFC, 0x1F, 
  0x80, 0xFF, 0x8F, 0x7F, 0xC0, 0xFF, 0x7F, 0xC0, 0xFF, 0x03, 0xC0, 0x3F, 
  0xF0, 0x1F, 0xFC, 0x1F, 0xE0, 0xFF, 0x87, 0x3F, 0xC0, 0xFF, 0x7F, 0xF0, 
  0xFF, 0x01, 0xF8, 0xFF, 0xF0, 0x0F, 0xFC, 0x1F, 0xE0, 0xFF, 0x87, 0x3F, 
  0xE0, 0xFF, 0x7F, 0xF8, 0xFF, 0x01, 0xFE, 0xFF, 0xF8, 0x0F, 0xFE, 0x0F, 
  0xF0, 0xFF, 0x87, 0x3F, 0xE0, 0xFF, 0x7F, 0xFC, 0xFF, 0x01, 0xFF, 0xFF, 
  0xF8, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0xC7, 0x3F, 0xE0, 0xFF, 0x3F, 0xFC, 
  0xFF, 0x81, 0xFF, 0xFF, 0xF8, 0xFF, 0xFF, 0x0F, 0xF0, 0xFF, 0xC3, 0x1F, 
  0xE0, 0xFF, 0x3F, 0xFC, 0xFF, 0xC0, 0xFF, 0x7F, 0xFC, 0xFF, 0xFF, 0x0F, 
  0xF8, 0xFF, 0xC3, 0x1F, 0xE0, 0xFF, 0x3F, 0xFC, 0xFF, 0xE0, 0xFF, 0x7F, 
  0xFC, 0xFF, 0xFF, 0x07, 0xF8, 0x03, 0xC0, 0x1F, 0x00, 0xFE, 0x01, 0xFE, 
  0x00, 0xF0, 0x3F, 0x70, 0xFC, 0xFF, 0xFF, 0x07, 0xF8, 0x03, 0xE0, 0x0F, 
  0x00, 0xFE, 0x00, 0xFE, 0x00, 0xF0, 0x1F, 0x60, 0xFC, 0xFF, 0xFF, 0x07, 
  0xF8, 0x03, 0xE0, 0x0F, 0x00, 0xFE, 0x00, 0xFE, 0x00, 0xF0, 0x07, 0x20, 
  0xFE, 0xFF, 0xFF, 0x07, 0xFC, 0xFF, 0xE1, 0x0F, 0x00, 0xFF, 0x00, 0xFF, 
  0x7F, 0xF8, 0x07, 0x00, 0xFE, 0x83, 0xFF, 0x03, 0xFC, 0xFF, 0xF1, 0x0F, 
  0x00, 0x7F, 0x00, 0xFF, 0x7F, 0xF8, 0x03, 0x00, 0xFE, 0x83, 0xFF, 0x03, 
  0xFC, 0xFF, 0xF0, 0x07, 0x00, 0x7F, 0x00, 0xFF, 0x7F, 0xFC, 0x03, 0x00, 
  0xFE, 0x81, 0xFF, 0x03, 0xFC, 0xFF, 0xF0, 0x07, 0x00, 0x7F, 0x00, 0xFF, 
  0x3F, 0xFC, 0x03, 0x00, 0xFF, 0xC1, 0xFF, 0x01, 0xFE, 0xFF, 0xF0, 0x07, 
  0x80, 0x3F, 0x80, 0xFF, 0x3F, 0xFC, 0x03, 0x00, 0xFF, 0xC1, 0xFF, 0x01, 
  0xFE, 0xFF, 0xF8, 0x07, 0x80, 0x3F, 0x80, 0xFF, 0x3F, 0xFC, 0x03, 0x10, 
  0xFF, 0xC1, 0xFF, 0x01, 0xFE, 0x00, 0xF8, 0x03, 0x80, 0x3F, 0x80, 0x3F, 
  0x00, 0xFC, 0x03, 0x0C, 0xFF, 0xC0, 0xFF, 0x01, 0xFF, 0x00, 0xF8, 0x03, 
  0xC0, 0x3F, 0x80, 0x3F, 0x00, 0xFC, 0x07, 0x0E, 0xFF, 0xE0, 0xFF, 0x00, 
  0x7F, 0x00, 0xF8, 0x03, 0xC0, 0x1F, 0xC0, 0x3F, 0x00, 0xFC, 0xFF, 0x0F, 
  0xFF, 0xE0, 0xFF, 0x00, 0xFF, 0x7F, 0xFC, 0xFF, 0xC1, 0x1F, 0xC0, 0xFF, 
  0x1F, 0xFC, 0xFF, 0x0F, 0x7F, 0xE0, 0xFF, 0x00, 0xFF, 0x3F, 0xFC, 0xFF, 
  0xC1, 0x1F, 0xC0, 0xFF, 0x0F, 0xF8, 0xFF, 0x07, 0x7E, 0xE0, 0xFF, 0x80, 
  0xFF, 0x3F, 0xFC, 0xFF, 0xE0, 0x1F, 0xC0, 0xFF, 0x0F, 0xF8, 0xFF, 0x07, 
  0x7C, 0xF0, 0x7F, 0x80, 0xFF, 0x3F, 0xFE, 0xFF, 0xE0, 0x0F, 0xE0, 0xFF, 
  0x0F, 0xF0, 0xFF, 0x07, 0xF8, 0xF0, 0x7F, 0x80, 0xFF, 0x1F, 0xFE, 0xFF, 
  0xE0, 0x0F, 0xE0, 0xFF, 0x0F, 0xE0, 0xFF, 0x07, 0xE0, 0xF0, 0x7F, 0x80, 
  0xFF, 0x1F, 0xFE, 0xFF, 0xE0, 0x0F, 0xE0, 0xFF, 0x07, 0x80, 0xFF, 0x03, 
  0x00, 0xF0, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x3C, 0x00, 0x00, 0xF8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x3F, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xF8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x1F, 0x00, 0x8F, 0xF7, 0xFF, 0x7C, 
  0xBC, 0xC7, 0xF3, 0xFF, 0xFC, 0xBC, 0x07, 0x00, 0x00, 0xFC, 0x1F, 0x00, 
  0x8F, 0x73, 0xFF, 0xFE, 0xBE, 0xC7, 0xFB, 0xFF, 0xFE, 0xBD, 0x03, 0x00, 
  0x00, 0xFC, 0x1F, 0x80, 0x8F, 0x73, 0xFF, 0xEF, 0xFE, 0xE7, 0xFB, 0x77, 
  0xEF, 0xFD, 0x03, 0x00, 0x00, 0xFC, 0x1F, 0x80, 0xDF, 0x7B, 0x9C, 0xE7, 
  0xFE, 0xF7, 0xE3, 0x71, 0xE7, 0xFD, 0x03, 0x00, 0x00, 0xFC, 0x0F, 0xC0, 
  0xDF, 0x79, 0x9E, 0xE3, 0xFE, 0xF3, 0xE3, 0x78, 0xE7, 0xFF, 0x03, 0x00, 
  0x00, 0xFC, 0x0F, 0xE0, 0xDF, 0x39, 0x8E, 0xF3, 0xFF, 0xFB, 0xE7, 0xF8, 
  0xE7, 0xFE, 0x01, 0x00, 0x00, 0xFC, 0x0F, 0xE0, 0xDF, 0x3F, 0x8E, 0x7F, 
  0xFF, 0xFF, 0xE7, 0x38, 0x7F, 0xEE, 0x01, 0x00, 0x00, 0xF8, 0x0F, 0x70, 
  0xDC, 0x1F, 0x0E, 0x3F, 0xFF, 0x9D, 0xF7, 0x38, 0x3F, 0xEF, 0x01, 0x00, 
  0x00, 0xF8, 0x0F, 0x00, 0x00, 0x03, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 
  0x08, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x0F, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x80, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
   
const char activeSymbol[] PROGMEM = {
    B00000000,
    B00000000,
    B00011000,
    B00100100,
    B01000010,
    B01000010,
    B00100100,
    B00011000
};

const char inactiveSymbol[] PROGMEM = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000
};

unsigned int counter = 0;
String rssi = "RSSI --";
String packSize = "--";
String packet ;

void logo()
{
  Heltec.display->clear();
  Heltec.display->drawXbm(0,5,logo_width,logo_height,logo_bits);
  Heltec.display->display();
}

void setup()
{
   //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
 
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  logo();
  delay(1500);
  Heltec.display->clear();
  
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->display();
  delay(1000);
}

void loop()
{
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  
  Heltec.display->drawString(0, 0, "Sending packet: ");
  Heltec.display->drawString(90, 0, String(counter));
  Heltec.display->display();

  // send packet
  LoRa.beginPacket();
  
/*
 * LoRa.setTxPower(txPower,RFOUT_pin);
 * txPower -- 0 ~ 20
 * RFOUT_pin could be RF_PACONFIG_PASELECT_PABOOST or RF_PACONFIG_PASELECT_RFO
 *   - RF_PACONFIG_PASELECT_PABOOST -- LoRa single output via PABOOST, maximum output 20dBm
 *   - RF_PACONFIG_PASELECT_RFO     -- LoRa single output via RFO_HF / RFO_LF, maximum output 14dBm
*/
  LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print("hello this is some extremely extra long test data lets add some extra data my friend okay how about we add some more test data to see if we can push this thing to its limit because i really want to transmit data on ipfs over LoRa lets try to fill up the program storage space with one really long string that we send through lora so that we can measure just how much data we can pipe through htis as if we were writing a really long email. but will this work? i have no idea hopefully it does because i really want to make LoRa IoT devies that let me made some really cool shit so lets pretend that we are writing an extra long emai lto see if we can pipe large amounts of data through this yo sly dog, this is really cool i love this stuff  okay i want to send some morte i need to go get ready");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
}