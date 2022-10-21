#include <Arduino.h>

int sensor = A0;
int rele = 5;
float umidade = 4;
int estadoSensor;
float estadoUmidade;

void setup() {
  pinMode(sensor, INPUT);
  pinMode(umidade, INPUT);
  pinMode(rele, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  estadoSensor = analogRead(sensor);
  // estadoUmidade = digitalRead(umidade);
  Serial.println(estadoSensor);
  // Serial.println(umidade);

  delay(500);

  if (estadoSensor > 928) {
    digitalWrite(rele, LOW);
    delay(10000);
    digitalWrite(rele, HIGH);
  }
  if (estadoSensor > 832) {
    digitalWrite(rele, LOW);
    delay(5000);
    digitalWrite(rele, HIGH);
  } else {
    digitalWrite(rele, LOW);
  }
}