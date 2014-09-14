

const int ledPin = 9;
const int temperaturePin = 0;

const int ledThreshold = 20.0; // Celsius


void setup()
{
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
}


void loop()
{


  float voltage, degreesC;


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
  Serial.println(degreesC);

  delay(1000);
}


float getVoltage(int pin)
{
  return (analogRead(pin) * 0.004882814);
}


