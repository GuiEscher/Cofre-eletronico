#include <LiquidCrystal_I2C.h>


#define echo_PIN 2
#define trigger_PIN 3
float distance;
int buzzer = 6;

// Configuração do display LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(buzzer, OUTPUT); //Defines the buzzer pin as Output
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
  tone(buzzer, 200/distance); // Activate the buzzer at the frequency relative to C in Hz (Dó)
  delay(100);   // Wait for a while to deactivate 
  noTone(buzzer); //Deactivate the buzzer