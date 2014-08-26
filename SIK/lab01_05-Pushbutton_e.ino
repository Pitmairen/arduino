
const int button1Pin = 2;
const int button2Pin = 3;
const int ledPin =  9;

const int MAX_BRIGHTNESS = 255;
const int FADE_SPEED = 2;

int current_brightness = MAX_BRIGHTNESS;

void setup()
{
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  pinMode(ledPin, OUTPUT);
}


void loop()
{


  // Button1 pressed
  while(digitalRead(button1Pin) == LOW && digitalRead(button2Pin) == HIGH)
  {
    current_brightness = constrain(current_brightness+1, 0, MAX_BRIGHTNESS);
    analogWrite(ledPin, current_brightness);
    delay(FADE_SPEED);
  }

  // Button2 pressed
  while(digitalRead(button1Pin) == HIGH && digitalRead(button2Pin) == LOW)
  {
    current_brightness = constrain(current_brightness-1, 0, MAX_BRIGHTNESS);
    analogWrite(ledPin, current_brightness);
    delay(FADE_SPEED);
  }

  analogWrite(ledPin, current_brightness);

}

