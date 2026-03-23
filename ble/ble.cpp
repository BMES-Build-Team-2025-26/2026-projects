#include "ble.h"

BLECharacteristic *rawDataCharacteristic = nullptr;
BLECharacteristic *pulseCharacteristic = nullptr;
BLEServer *pServer = nullptr;
bool deviceConnected = false;

class bleCallback: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("Device Connected!");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("Device Disconnected!");
      BLEDevice::startAdvertising(); 
      Serial.println("Restarted Advertising...");
    }
};

void bleInit(char *deviceName) {
  BLEDevice::init(deviceName);
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new bleCallback());

  //pulse service
  BLEService *pulseService = pServer->createService(pulseServiceUUID);
  pulseCharacteristic =
    pulseService->createCharacteristic(pulseCharacteristicUUID, BLECharacteristic::PROPERTY_NOTIFY);
  pulseCharacteristic->setValue("0");
  pulseService->start();

  //raw data service
  BLEService *rawDataService = pServer->createService(rawDataServiceUUID);
  rawDataCharacteristic =
    rawDataService->createCharacteristic(rawDataCharacteristicUUID, BLECharacteristic::PROPERTY_NOTIFY);
  rawDataCharacteristic->setValue("0");
  rawDataService->start();
  
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(pulseServiceUUID);
  pAdvertising->addServiceUUID(rawDataServiceUUID);

  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  randomSeed(analogRead(5));
}


void setRawData(uint16_t data) {
  uint8_t payload[2];

  payload[0] = data & 0xFF; //LSB
  payload[1] = (data >> 8) & 0xFF; //MSB
  rawDataCharacteristic->setValue(payload, 2);
  rawDataCharacteristic->notify();
}

// Helper function to convert a float to a basic BLE SFLOAT
uint16_t floatToSFLOAT(float value) {
    uint16_t mantissa = (uint16_t)round(value);
   
    uint16_t sfloat = mantissa & 0x0FFF; 
    
    return sfloat;
}

void setPulseOxData(float pulse, float pulseOx) {
    uint8_t payload[5];
    payload[0] = 0x00;
    
    // Convert floats to 16-bit SFLOATs
    uint16_t spo2_sfloat = floatToSFLOAT(pulseOx);
    uint16_t pr_sfloat = floatToSFLOAT(pulse);
    
    // Byte 1, 2: SpO2
    payload[1] = spo2_sfloat & 0xFF;         // LSB
    payload[2] = (spo2_sfloat >> 8) & 0xFF;  // MSB
    
    // Byte 3, 4: Pulse Rate
    payload[3] = pr_sfloat & 0xFF;         // LSB
    payload[4] = (pr_sfloat >> 8) & 0xFF;  // MSB
    
    if (pulseCharacteristic != nullptr) {
        pulseCharacteristic->setValue(payload, 5);
        pulseCharacteristic->notify();
        Serial.println("Pulse BLE Sent!");
    } else {
        Serial.println("Error: Characteristic not initialized.");
    }
}
