#include <Arduino.h>
#include <TM1637Display.h>
#include "DHT.h"
#define DHTPIN 5  
#define CLK 3
#define DIO 2
#define DHTTYPE DHT11
#define LIT_Q SEG_F | SEG_A | SEG_B | SEG_G | SEG_C
#define LIT_B SEG_F | SEG_E | SEG_G | SEG_D| SEG_C
#define circle SEG_F | SEG_A | SEG_B | SEG_G
#define LIT_F SEG_A | SEG_E | SEG_F |  SEG_G
const uint8_t temp[] = {circle, LIT_F};
const uint8_t humid[] = {LIT_Q, LIT_B};

TM1637Display display(CLK, DIO);
DHT dht = DHT(DHTPIN, DHTTYPE, 6);
void setup() {
  display.setBrightness(2);
  Serial.begin(9600);
  dht.begin();
  //delay(500);
}

void temperature(int f){
  display.showNumberDec(f, false, 2, 0); 
  display.setSegments(temp, 2, 2);
  Serial.print("temperature: ");
  Serial.print(f);
  Serial.println("°F");
}

void humidity(int h){
  display.showNumberDec(h, false, 2, 0); 
  display.setSegments(humid, 2, 2);
  Serial.print("humidity: ");
  Serial.print(h);
  Serial.println("%");
}

void loop(){
  delay(2000);
  int f = dht.readTemperature(true);
  temperature(f);
  delay(2000);
  int h = dht.readHumidity();
  humidity(h);
}