// Circuit Key:
// Voltage divider output should be plugged into A0
// LED should be plugged into D2


const int sensorPin = A0;
const int LEDPin = 2;
int sensorVal;
int ambientPressure;

const int thresh = 900;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, HIGH);
  ambientPressure = analogRead(sensorPin);
  digitalWrite(LEDPin, LOW);
}



void loop() {
  // put your main code here, to run repeatedly:
  sensorVal = analogRead(sensorPin);
  Serial.println(sensorVal);

  if(sensorVal < ambientPressure - thresh){
    digitalWrite(LEDPin, HIGH);
  }
  else{
    digitalWrite(LEDPin, LOW);
  }
}
