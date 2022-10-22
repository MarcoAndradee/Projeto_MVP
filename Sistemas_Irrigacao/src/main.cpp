#include <Arduino.h>
#include <ESP8266Wifi.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int sensor_solo = A0;
int rele = 5;
int estadoSensor;
float temperatura;
float umidade;

void setup() {
  Serial.begin(9600);
  delay(50);
  dht.begin();
  pinMode(sensor_solo, INPUT);
  pinMode(umidade, DHT11);
  pinMode(rele, OUTPUT);

}

void loop() {
 estadoSensor = analogRead(sensor_solo);
  Serial.println(estadoSensor);
  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();
  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" ºC");
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println(" %");

  delay(1000);

  if (estadoSensor > 928) {
    digitalWrite(rele, LOW);
    delay(10000);
    digitalWrite(rele, HIGH);
  }
  if ((estadoSensor > 832) || ((temperatura > 60) && (umidade < 30))) {
    digitalWrite(rele, LOW);
    delay(5000);
    digitalWrite(rele, HIGH);
  } else {
    digitalWrite(rele, LOW);
  }
}