
const int sensorPin = 0;
const int ledPin = 9;

int lightLevel, high = 0, low = 1023;


void setup()
{
  pinMode(ledPin, OUTPUT);
}


void loop()
{

  lightLevel = analogRead(sensorPin);


  manualTune();


  analogWrite(ledPin, lightLevel);
}


void manualTune()
{

  // The from-range 500-850 seems to work well for the lighting condition in the
  // room this code was tested.
  lightLevel = map(lightLevel, 500, 850, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);


}


