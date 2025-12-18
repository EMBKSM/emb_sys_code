#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 8); // RX: 9, TX: 8

void setup() {
  mySerial.begin(9600);
}

void loop() {
  mySerial.write('a');

  delay(10); 
}