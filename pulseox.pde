import processing.serial.*;

Serial myPort;
int[] serialValues;

void setup() {
  myPort = new Serial(this, "COMX", 115200); //replace COMX with your serial port
  myPort.bufferUntil('\n');
}

void draw() {

}

/***********************
DO NOT MODIFY
void serialEvent: reads data from Serial port
Reads int input(formatted as x1,x2,x3,x4) into serialValues array
***********************/
void serialEvent(Serial p) {
  String rawData = p.readStringUntil('\n');
  if (rawData != null) {
    String inData = trim(rawData);
    String[] list = split(inData, ',');
    serialValues = new int[list.length];
    for (int i = 0; i < list.length; i++) {
      serialValues[i] = int(list[i]);
    }
}
