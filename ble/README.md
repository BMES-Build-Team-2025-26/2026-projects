# BLE Functionality
These helper files are designed to work with [Build Team Pulse Ox App (iOS)](https://github.com/tsaimatthew/buildTeamPulseOxApp). Ideally, you would run this app on your iPhone following [these instructions](https://developer.apple.com/documentation/xcode/running-your-app-in-simulator-or-on-a-device) and putting your phone in Developer Mode.
We have limited resources available to troubleshoot BLE problems, and you are welcome to extend and modify this code, as well as the app code, as you see fit. These repositories provide the bare minimum to visualize your data.
## How to Use
1. To use these, include the ble.cpp and ble.h files in the same directory as your main .ino Arduino file. They should appear as tabs in the Arduino IDE.
2. Next, ensure ```#include "ble.h"``` is at the top of your code.
3. call ```setRawData(float PPG);``` to plot your raw data in a graph and ```setPulseOxData(float bpm, float pulseOx);``` to send your filtered beats per minute (bpm) and SpO2 percentage (pulseox) to the app.
## Underlying Functionality
BLE involves categorizing your data in a GATT with unique services and characteristics. I have created two services, a pre-defined pulse ox service to send your filtered SpO2 and pulse data, and a custom service to send your raw PPG signal so you can visualize your pulse waveforms in the app.
[Further Reading](https://novelbits.io/bluetooth-low-energy-ble-complete-guide/)
