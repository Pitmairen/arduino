
const int sensorPin = 0;
const int ledPin = 9;

int lightLevel, high = 0, low = 1023;


void setup()
{
  pinMode(ledPin, OUTPUT);

  // Setup the serial connection
  Serial.begin(9600);
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


  // Print the values of high and low:
  Serial.print("Low: ");
  Serial.print(low);
  Serial.print(" - High:");
  Serial.println(high);

  lightLevel = map(lightLevel, low+30, high-30, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);


}

