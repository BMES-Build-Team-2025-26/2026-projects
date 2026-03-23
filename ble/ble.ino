#include "ble.h"

void setup() {
  Serial.begin(115200);
  bleInit("pulseOx");
}

int ctr = 0;
void loop() {
  // put your main code here, to run repeatedly:
  setRawData(random(0, 4096));
  
  if (ctr >= 1000/20) {
    setPulseOxData(static_cast<float>(random(80, 120)), static_cast<float>(random(80, 100)));
    ctr = 0;
  } else ctr++;
  delay(20);
}
