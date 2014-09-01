
const int button1Pin = 2;
const int button2Pin = 3;
const int ledPin =  9;

const int MAX_BRIGHTNESS = 255;

// Delay between each change in brightness. In milliseconds.
const int FADE_SPEED = 5;


// Current brightness of the LED
int current_brightness = MAX_BRIGHTNESS;

void setup()
{
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  pinMode(ledPin, OUTPUT);
}


void loop()
{

  // Button1 pressed. (and not button2 at the same time)
  if(digitalRead(button1Pin) == LOW && digitalRead(button2Pin) == HIGH){

    // Increase the current brightness by one. By using constrain() the
    // brightness will not go beyond maximum brightness.
    current_brightness = constrain(current_brightness+1, 0, MAX_BRIGHTNESS);
  }

  // Button2 pressed. (and no button1 at the same time)
  else if(digitalRead(button1Pin) == HIGH && digitalRead(button2Pin) == LOW){

    // Lower the current brightness by one. By using constrain() the
    // brightness will not go below 0.
    current_brightness = constrain(current_brightness-1, 0, MAX_BRIGHTNESS);
  }

  // Set current brithness
  analogWrite(ledPin, current_brightness);
  delay(FADE_SPEED);
}

