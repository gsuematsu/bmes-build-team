
const int sensorPin = A5;
const int LEDPin = 2;
int sensorVal;
int ambientTemp;

const int thresh = 30;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, HIGH);
  ambientTemp = analogRead(sensorPin);
  digitalWrite(LEDPin, LOW);
}



void loop() {
  // put your main code here, to run repeatedly:
  sensorVal = analogRead(sensorPin);
  Serial.println(sensorVal);

  if(sensorVal < ambientTemp - thresh){
    digitalWrite(LEDPin, HIGH);
  }
  else{
    digitalWrite(LEDPin, LOW);
  }
}
