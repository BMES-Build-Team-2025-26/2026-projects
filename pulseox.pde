import processing.serial.*;
import cc.arduino.*;
import org.firmata.*;

Arduino myESP;

void setup() {
  myESP = new Arduino(this, Arduino.list()[0], 115200);

}

void draw() {

}
