#include "mesafeSiniri.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mesafePinler(9,10);

}

void loop() {
  Serial.println(mesafe());

}
