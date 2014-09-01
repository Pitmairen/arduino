
const int button1Pin = 2;
const int button2Pin = 3;
const int ledPin =  13;

// store the current LED state
int led_state = HIGH;

void setup()
{
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  pinMode(ledPin, OUTPUT);
}


void loop()
{

  int button1State, button2State;

  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);


  // Button1 pressed
  if (button1State == LOW && button2State == HIGH)
  {
    led_state = HIGH; // LED On
  }
  // Button2 pressed
  else if (button1State == HIGH && button2State == LOW)
  {
    led_state = LOW; // LED Off
  }

  // Set the current LED state.
  digitalWrite(ledPin, led_state);

}


