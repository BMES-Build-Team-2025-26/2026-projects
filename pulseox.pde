import processing.serial.*;
import cc.arduino.*;
import org.firmata.*;

Arduino myESP;
int pin = 10; //Connect to pin 4 on ESP32

void setup() {
  myESP = new Arduino(this, Arduino.list()[0], 115200);

}

void draw() {

}
