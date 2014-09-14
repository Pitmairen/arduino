
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

  // Tune the high-low range
  autoTune();

  analogWrite(ledPin, lightLevel);
}



void autoTune()
{

  if (lightLevel < low)
  {
    low = lightLevel;
  }


  if (lightLevel > high)
  {
    high = lightLevel;
  }

  int padding = 30;

  // Dynamically change the padding of the high and low values.
  // This is done because if we use a static padding like in the
  // original code, and the difference between the high and low is less than
  // twice the padding, the "fromLow" argument of the map function will
  // be bigger than the "fromHigh" arguments and we get weird results until the
  // difference between high and low get large enough.
  if(high-low <= padding*2){
    // Just take half the difference between high and low and subtract one.
    padding = (high-low) / 2 - 1;
  }

  // Swap the direction of the toLow and toHigh arguments to reverse the
  // direction of the lightLevel. It will now light up when the lightLevel is
  // low.
  lightLevel = map(lightLevel, low+padding, high-padding, 255, 0);


  lightLevel = constrain(lightLevel, 0, 255);

}

