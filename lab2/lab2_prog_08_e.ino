

const int ledPin = 9;
const int temperaturePin = 0;
const int potPin = 1;



void setup()
{
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
}


void loop()
{


  float voltage, degreesC;
  int ledThreshold;


  // Read the threshold from the Potmeter
  ledThreshold = analogRead(potPin);
  // Convert the value into the range 0-50 Celsius.
  ledThreshold = map(ledThreshold, 0, 1023, 0, 50);

  voltage = getVoltage(temperaturePin);

  degreesC = (voltage - 0.5) * 100.0;

  // If the temperature is above the threshold we turn on the LED.
  if(degreesC > ledThreshold){
    digitalWrite(ledPin, HIGH);
  }
  else{
    digitalWrite(ledPin, LOW);
  }


  Serial.print("voltage: ");
  Serial.print(voltage);
  Serial.print("  deg C: ");
  Serial.print(degreesC);
  Serial.print("  threshold: ");
  Serial.println(ledThreshold);

  delay(1000);
}


float getVoltage(int pin)
{
  return (analogRead(pin) * 0.004882814);
}


