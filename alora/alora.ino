#include <Arduino.h>
#include <Wire.h>
#include <AloraSensorKit.h>
#include <HardwareSerial.h>
HardwareSerial loraSerial(1);

#include "FabrickLoRa.h"
#include "AloraFabrickClient.h"

// Defines RX and TX pins that connected with LoRa shield
#define LORA_RX 33
#define LORA_TX 23

// Instantiate the AloraSensorKit class and global variable of Alora's SensorValue structure.
AloraSensorKit sensorkit;
SensorValues lastSensorData;

// Insantiate the FabrickLoRa and AloraFabrickClient object.
FabrickLoRa fabrick;
AloraFabrickClient aloraFabrick;

// Define the device ID of your device.
// This value is obtained from Fabrick device manager
#define FABRICK_DEVICE_ID "[your device ID here]"

void setup() {
    Serial.begin(9600);
    loraSerial.begin(9600, SERIAL_8N1, LORA_RX, LORA_TX);
    if (!fabrick.begin()) {
        Serial.pritnln("Failed to initialize communication with LoRa shield!");
        // don't continue the program if we fail
        while (1);
    }
    aloraFabrick.begin(&fabrick, FABRICK_DEVICE_ID);
    // initialize sensor kit
    sensorKit.begin();
}


void loop() {
    sensorKit.run();
    lastSensorData = sensorKit.getLastSensorData();
    // send temperature data from BME280 sensor
    if (aloraFabrick.sendTemperature(lastSensorData.T1)) {
        Serial.println("Success send temperature tx packet");
    } else {
        Serial.println("Failed to send temperature tx packet");
    }
    delay(3000);
    // send humidity data from BME280 sensor
    if (aloraFabrick.sendHumidity(lastSensorData.H1)) {
        Serial.println("Success send humidity tx packet");
    } else {
        Serial.println("Failed to send humidity tx packet");
    }
    delay(3000);
}
