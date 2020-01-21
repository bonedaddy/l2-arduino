int ledPin = 10; // define digital pin 10
void setup()
{
    pinMode(ledPin, OUTPUT);// define LED pin as output
}
void loop()
{
    for (int a=0; a<=255;a++)// set the LED to be brighter gradually 
    {
        analogWrite(ledPin,a); // turn on LED, regulate light brightness, ranging from 0-255, 255 is the brightest
        delay(10); // wait for 0.01S
    }
    for (int a=255; a>=0;a--) // set LED to be dimming gradually
    {
        analogWrite(ledPin,a); // turn on LED, regulate light brightness, ranging from 0-255, 255 is the brightest
        delay(10); // wait for 0.01S
    }
}