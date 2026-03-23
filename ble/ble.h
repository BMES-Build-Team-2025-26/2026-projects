#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define pulseServiceUUID        "1822"
#define pulseCharacteristicUUID "2A5F"

#define rawDataServiceUUID        "f10cae14-7337-4372-9154-e1fd14b6b725"
#define rawDataCharacteristicUUID "92dce908-b66d-4fa4-902d-99d74266e74c"

class bleCallback;
extern BLECharacteristic *rawDataCharacteristic;
extern BLECharacteristic *pulseCharacteristic;
extern BLEServer *pServer;
extern bool deviceConnected;

void bleInit(char *deviceName);
void setPulseOxData(float pulse, float pulseOx);
void setRawData(uint16_t data);
