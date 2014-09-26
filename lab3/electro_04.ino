
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

  // Turn all the leds off to make sure only one led is on at a time.
  allLedsOff();

  // Turn on the red led if the voltage is over the limit.
  if(potVoltage > alertLimit){
    ledOn(alertPin);
  }
  // If the voltage is below 0.1 we do nothing.
  else if (potVoltage > 0.1) {

    // Create an int from the potVoltage and use that to select the
    // correct ledpin. When the voltage is between
    // 0-1 this will select index 0, when it is between 1-2 it will
    // select index 1, and so on.
    ledOn(ledPins[int(potVoltage)]);
  }

  Serial.print("Potmeter Voltage: ");
  Serial.println(potVoltage);

  delay(100);

}


void ledOn(int pin)
{
   digitalWrite(pin, HIGH);
}

void allLedsOff()
{
   for(int i=0; i<ledCount; ++i){
      digitalWrite(ledPins[i], LOW);
   }
}

float readVoltage(int pin)
{
  // Convert the value from analogRead int the real voltage.
  return analogRead(pin) * (5.0/1023.0);
}


