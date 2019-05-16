// Reads voltage from pin A0 an displays voltage to appear similar to EKG //<>//

import processing.serial.*;
import cc.arduino.*;

Arduino arduino;

int pinAnalog = 0;

int val;      // Data received from the Arduino
int[] values;
float zoom;

int oneSec;
int index;
int gap;

void setup() 
{
  size(1280, 480);
  // Prints out the available serial ports.
  println(Arduino.list());
  
  // Modify this line, by changing the "0" to the index of the serial
  // port corresponding to your Arduino board (as it appears in the list
  // printed by the line above).
  arduino = new Arduino(this, Arduino.list()[1], 57600);
  
  values = new int[width];
  zoom = 2.0f;
  oneSec = 57;
  oneSec *= zoom;
  index = 0;
  gap = 10;
  smooth();
  for (int i = 0; i < values.length; i++){
    values[i] = -1;
  }
}

int getY(int val) {
  return (int)(height - val / 1023.0f * (height - 1) - 1);
}

int getValue() {
  int value = -1;
  
  value = arduino.analogRead(pinAnalog);
  
  println(value);
  return value;
}

void storeValue(int value) {
  boolean isStored = false;
  int k = 1;
  
  for (int i = 0; i < values.length; i++){
    if (values[i] == -1 && !isStored){
      values[i] = value;
      isStored = true;
      
      while (k <= gap && i+k < displayWidth){
         values[i+k] = -1;
         k++;
      }
    }
  }
  index++;
}

void restart(){
 for (int i = 0; i < gap; i++)
    values[i] = -1;
 index = 0;
}

void drawLines() {
  strokeWeight(1);
  stroke(0, 255, 0);
  
  int displayWidth = (int) (width / zoom);
 
  int k = 0;
  
  int x0 = 0;
  int y0 = getY(values[k]);
  for (int i=1; i<displayWidth; i++) {
    k++;
    int x1 = (int) (i * (width-1) / (displayWidth-1));
    int y1 = getY(values[k]);
    if (values[k-1] != -1 && values[k] != -1)
      line(x0, y0, x1, y1);
    x0 = x1;
    y0 = y1;
    
    if (index == displayWidth-1 && values[k] != -1)
      restart();
     
  }

}

void drawGrid() {
  strokeWeight(1);
  stroke(63);
  for (int i = 0; i <= 10 * width/oneSec; i++){
    int time = i * oneSec/10;
    if (time % oneSec != 0){
      line(time, 0, time, height);
    }
  }
  for (int i = 1; i < 40; i++){
    line(0, i*height/40, width, i*height/40);
  }
  
  stroke(255);
  for (int i = 0; i <= width/oneSec; i++){
    int time = i * oneSec;
    line(time, 0, time, height);
  }
  for (int i = 0; i <= 4; i++){ //<>//
    line(0, i*height/4, width, i*height/4);
  }
}

void keyReleased() {
  switch (key) {
    case '+':
      zoom *= 2.0f;
      oneSec *= 2;
      println(zoom);
      if ( (int) (width / zoom) <= 1 )
        zoom /= 2.0f;
      break;
    case '-':
      zoom /= 2.0f;
      oneSec /= 2;
      if (zoom < 1.0f)
        zoom *= 2.0f;
      break;
  }
}

void draw()
{ //<>//
  background(0);
  drawGrid();
  val = getValue();
  if (val != -1) {
    storeValue(val);
  }
  drawLines();
}
