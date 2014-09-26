
const int diodeOutPin = 10;


void setup() {

  pinMode(diodeOutPin, OUTPUT);

}


void loop() {

  // Increase the voltage on the diode circuit from 0 to 5V with
  // 0.5 V increments.
  for(int i=0; i<=10; ++i){

    // Increase the voltage by 0.5 for every iteration of the loop
    analogWrite(diodeOutPin, 255 * (i*0.5/5.0));

    // Delay to get time to measure the circuit with a multimeter
    delay(10000);
  }

}


