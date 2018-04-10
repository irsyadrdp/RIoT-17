#include <FabrickLora.h>

//****************************************
// Initialisations
//****************************************
// Pins assignment
// Default pins assignment located at Fabrick.h
SoftwareSerial lora_serial(pinLoraRx, pinLoraTx);       // Software serial for LoRa module
DHT22          dht(pinTemp);                            // Air temp./humidity sensor 
Ultrasonic     ultrasonic(pinUltraTrig, pinUltraEcho);  // Ultrasonic/range sensor
SoftwareSerial pm25_serial(pinPM25Rx, pinPM25Tx);       // PM2.5 sensor

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EDIT HERE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Device ID
String device_id = "6fec7c3d";
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~END~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Fabrick library
FabrickLora fabrick;      

// PM25
void PM25_listen(){
  if(!pm25_serial.isListening()) 
      pm25_serial.listen();  
}

//****************************************
// Setup
//****************************************
void setup() {
  // Initialise serial for debugging
  Serial.begin(9600);
  Serial.println("***********************************************************************"); 
  Serial.println("                  Fabrick LoRa Development Kit");
  Serial.println("***********************************************************************");    
  
  // Setup LoRa DK
  fabrick.lora_dk_begin( &lora_serial, &dht, &ultrasonic, &pm25_serial, &Serial);  

  // Initialise PM2.5 sensor
  PM25.init(&pm25_serial, &Serial, PM25_listen);
}

//****************************************
// Main Loop
//****************************************
void loop() {
  // Delay to let LoRa startup
  delay(10000);

  // Send sound data
  fabrick.lora_send_sound(device_id);
  
  // Send temperature data
  fabrick.lora_send_temp(device_id);

  // Send humidity data
  fabrick.lora_send_humid(device_id);

  // Send range data
  fabrick.lora_send_range(device_id); 
  
  // Send PM25 data
  fabrick.lora_send_pm25(device_id, PM25.read());
}
