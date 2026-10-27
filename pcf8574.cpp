//lib_deps = robtillaart/PCF8574 @ ^0.3.5

#include <Arduino.h>
#include <Wire.h>
#include <PCF8574.h>

PCF8574 pcf8574(0x20);

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);

  pcf8574.begin();
  Serial.println("Rozsvícení všech LED najednou!");
}

void loop() {

  for (int i = 0; i < 8; i++) {
    pcf8574.write(i, LOW);
  }
}