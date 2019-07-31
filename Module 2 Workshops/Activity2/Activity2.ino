int yLED = 9;// pin for yellow LED
int rLED = 10; // pin for red LED
unsigned long startTime; // use unsigned long for time variables

void setup() {
  // set both pins to output
  pinMODE(yLED, OUTPUT);
  pinMODE(rLED, OUTPUT);
  digitalWrite(yLED, HIGH);// yellow on
  digitalWrite(rLED, LOW);// red off
  startTime = millis(); // stores time of last state change
}

void loop() {
  if ((millis() - startTime) >= 5000)
  {
     digitalWrite(yLED, LOW); // yellow off
     for (int i = 0; i < 10; i++)// for 10 times...
     {
        //blink
        digitalWrite(rLED, HIGH);
        delay(500);
        digitalWrite(yLED, LOW);
        delay(500);
     }
     digitalWrite(yLED, HIGH); // yellow back on
     startTime = millis(); // update start time
  }
}
