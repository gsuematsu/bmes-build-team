pinBTN = 4;
pinLED = 10;
bool LEDon = false; // boolean to keep track of LED state

void setup() {
  pinMode(pinBTN, INPUT);
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, LOW);
}

void loop() {
  // if the button is pressed but the LED isn't on yet
  if (digitalRead(pinBTN)== HIGH && !LEDon)
  {
    digitalWrite(pinLED, HIGH); // turn LED on
    LEDon = true; // update boolean
  }
  // if the button isn't pressed but the LED has't been turned off yet
  if (digitalRead(pinBTN) == LOW && LEDon)
  {
    digitalWrite(pinLED, LOW); // turn LED off
    LEDon = false; // update boolean
  }
}
