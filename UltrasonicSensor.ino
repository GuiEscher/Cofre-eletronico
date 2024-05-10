/*****************************************************************************
* HC-SR04 Ultrasonic Sensor
* Code to turn a LED on when an object is within 50cm range
* Author: Kelen C. Teixeira Vivaldini
******************************************************************************/
#include <LiquidCrystal_I2C.h>


#define echo_PIN 2
#define trigger_PIN 3
int distance;

// Configuração do display LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Inicialização do display LCD
  lcd.init();
  lcd.backlight();
  // Mensagem de boas-vindas no LCD
  lcd.setCursor(0, 0);
  lcd.print("Distancia: ");
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(trigger_PIN, OUTPUT);
  pinMode(echo_PIN, INPUT);
}

float readDistance() {
  digitalWrite(trigger_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_PIN, LOW);
  int duration = pulseIn(echo_PIN, HIGH);
  distance = duration * 0.034/2;
  lcd.clear();
  lcd.print("Distancia: ");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.setCursor(6,1);
  lcd.print("cm");
  
  return distance; //Constante obtida com calibração
}

void loop() {
  distance = readDistance();
  bool isNearby = distance < 50;
  digitalWrite(LED_BUILTIN, isNearby);
  delay(100);
}