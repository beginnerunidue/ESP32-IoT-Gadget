#include <Arduino.h>
#include "sensor_readings.h"
#include "settings.h"  // Ther order is importante!

Adafruit_BME280 bme; // I2C

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  bool status;

  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  refresh_readings(bme); // Parsing the bme object to the function as bmt is only "global" in this file.
  delay(1000);
}

