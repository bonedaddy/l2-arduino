int redLED    = 10; // initialize red pin 10.
int yellowLED = 7; // initialize yellow pin 7.
int greenLED  = 4; // initialize green pin 4.
void setup()
{
    pinMode(redLED, OUTPUT);// set the pin with red LED as “output”
    pinMode(yellowLED, OUTPUT); // set the pin with yellow LED as “output”
    pinMode(greenLED, OUTPUT); // set the pin with green LED as “output”
}
void loop()
{
    digitalWrite(greenLED, HIGH);//// turn on green LED
    delay(2000);// wait 2 seconds
    digitalWrite(greenLED, LOW); // turn off green LED
    for(int i=0;i<3;i++)// blinks for 3 times
    {
        delay(200);// wait 0.2 second
        digitalWrite(yellowLED, HIGH);// turn on yellow LED
        delay(200);// wait 0.2 second
        digitalWrite(yellowLED, LOW);// turn off yellow LED
    } 
    delay(200);// wait 0.2 second
    digitalWrite(redLED, HIGH);// turn on red LED
    delay(2000);// wait 2 second
    digitalWrite(redLED, LOW);// turn off red LED
}