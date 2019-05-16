#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (!SD.begin(6)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  pinMode(A0, INPUT);
}

void loop() {
  int val = analogRead(A0);
  Serial.println(val);
  myFile = SD.open("data.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to data.txt...");
    myFile.println(val);
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

}
