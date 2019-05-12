import processing.serial.*;
import cc.arduino.*;

Arduino arduino;

int pinAnalog = 0;

int val;      // Data received from the Arduino
int[] values;
int index = 0;

void setup() {
  size(1280, 600);
  
  // Prints out the available serial ports.
  println(Arduino.list());
  
  // Modify this line, by changing the "0" to the index of the serial
  // port corresponding to your Arduino board (as it appears in the list
  // printed by the line above).
  arduino = new Arduino(this, Arduino.list()[2], 57600);
  
  values = new int[width];
  for (int i = 0; i < values.length; i++){
    values[i] = -1;
  }
  background(0);
}

void draw() {
  background(0);
  
  drawLines();
  storeVal();
  plotValues();
}

void storeVal(){
  int val = arduino.analogRead(pinAnalog);
  if(index <= width - 1){
    values[index] = val;
  }
  else{
    for(int i = 0; i < values.length - 1; i++){
      values[i] = values[i+1];
    }
    values[values.length - 1] = val;
  }
  if(index < width){
    index++;
  }
}

void plotValues(){
  strokeWeight(1);
  stroke(255);
 
  for(int i = 0; i < values.length - 1; i ++){
    if(values[i] != -1 && values[i+1] != -1){
      line(i, getY(values[i]), i + 1, getY(values[i+1]));
    }
  }
}

int getY(int val){
  int mapVal = (int) map(val, 0, 1023, 0, height);
  int y = height - mapVal;
  
  return y;
}

void drawLines(){
  float textScale = 0.025;
  strokeWeight(1);
  stroke(127);
  fill(127);
  
  for(int i = 0; i < 6; i++){
    line(0, i * height/5, width, i * height/5);
  }
  
  textSize(textScale * height);
  
  text("0V", .001 * width, height);
  text("1V", .001 * width, 4 * height/5);
  text("2V", .001 * width, 3 * height/5);
  text("3V", .001 * width, 2 * height/5);
  text("4V", .001 * width, height/5);
  text("5V", .001 * width, textScale * height);
}