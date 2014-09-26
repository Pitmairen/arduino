
const int potPin = A0;
const int ledPins[] = {2, 3, 4, 5, 6, 7};
const int alertPin = 7;

// The voltage limit for the red led.
const float alertLimit= 4.8; // in Volt

const int ledCount = sizeof(ledPins)/sizeof(int);


void setup() {

  // Set the ledPins to output mode
  for(int i=0; i<ledCount; ++i){
    pinMode(ledPins[i], OUTPUT);
  }

  // Setup the serial connection
  Serial.begin(9600);


}


void loop() {

  float potVoltage = readVoltage(potPin);


  // If the voltage is very low w just turn off all the LEDs.
  if(potVoltage < 0.1){
    allLedsOff();
  }
  else{

    // If the voltage is above 0.1 we turn on one LED every time the voltage
    // increases by 1V.

    for(int i=0; i <= ledCount; i++){

      // If the LED pin index is below or equal to the integer value
      // of the current voltage we turn it on. If not we turn it off.
      if(i <= int(potVoltage))
        ledOn(ledPins[i]);
      else
        ledOff(ledPins[i]);
    }

    // If the voltage is above the limit we make sure the alter LED is on.
    if(potVoltage > alertLimit){
       ledOn(alertPin);
    }
  }

  Serial.print("Potmeter Voltage: ");
  Serial.println(potVoltage);

  delay(100);

}


void ledOn(int pin)
{
   digitalWrite(pin, HIGH);
}

void ledOff(int pin)
{
   digitalWrite(pin, LOW);
}


void allLedsOff()
{
   for(int i=0; i<ledCount; ++i){
      ledOff(ledPins[i]);
   }
}

float readVoltage(int pin)
{
  // Convert the value from analogRead int the real voltage.
  return analogRead(pin) * (5.0/1023.0);
}


