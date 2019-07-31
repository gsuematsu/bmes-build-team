int pinLED = 9; // digital pin for LED

void setup() {
  pinMode(pinLED, OUTPUT); // set the LED pin to output
  digitalWrite(pinLED, LOW); // initially have the LED off
}

void loop() {
  if (millis() >= 5000)// once 5000 ms has passed
    digitalWrite(pinLED, HIGH); // turn LED on
}
