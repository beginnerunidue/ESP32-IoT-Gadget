/***************************************************************************
This is a library for the BMP280 humidity, temperature & pressure sensor
 
Designed specifically to work with the Adafruit BMEP280 Breakout 
----> http://www.adafruit.com/products/2651
 
These sensors use I2C or SPI to communicate, 2 or 4 pins are required 
to interface.
 
Adafruit invests time and resources providing this open source code,
please support Adafruit andopen-source hardware by purchasing products
from Adafruit!
 
Written by Limor Fried & Kevin Townsend for Adafruit Industries. 
BSD license, all text above must be included in any redistribution
***************************************************************************/
 
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <U8g2lib.h>
 
#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10
uint16_t counter1 = 0;
Adafruit_BMP280 bme; // I2C
//Adafruit_BMP280 bme(BMP_CS); // hardware SPI
//Adafruit_BMP280 bme(BMP_CS, BMP_MOSI, BMP_MISO, BMP_SCK);
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
 
void setup() {
Serial.begin(9600);
Serial.println(F("BMP280 test"));
 
if (!bme.begin()) { 
Serial.println("Could not find a valid BMP280 sensor, check wiring!");
while (1);
}

u8g2.begin();
}
 
void loop() {
Serial.print("Temperature = ");
Serial.print(bme.readTemperature());
Serial.println(" *C");
 
Serial.print("Pressure = ");
Serial.print(bme.readPressure());
Serial.println(" Pa");
 
Serial.print("Approx altitude = ");
Serial.print(bme.readAltitude(1013.25)); // this should be adjusted to your local forcase
Serial.println(" m");
 
Serial.println();
  u8g2.clearBuffer();					// clear the internal memory
  //u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.setFont(u8g2_font_missingplanet_tn);	// choose a suitable font
  char counterarray[6];
  sprintf(counterarray,"%d",counter1);
  u8g2.drawStr(0,15,counterarray);	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  counter1++;
  delay(2000);
}