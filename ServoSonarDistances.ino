#include <Servo.h>

#define echo_PIN 2
#define PINO_SERVO 5
#define trigger_PIN 3
float distance;
int buzzer = 6;
// Objeto do servo motor
Servo servo;

void setup() {
  pinMode(buzzer, OUTPUT); //Defines the buzzer pin as Output
  Serial.begin(9600);
   // Inicialização do servo motor
  servo.attach(PINO_SERVO);
  servo.write(0); // Fecha a caixa inicialmente

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
  
  return distance; //Constante obtida com calibração
}

void movimento(){
  int angulo = 0;
  float menor = 4000;
  int indice = 0;
  float vet[180] = {0};
  for(angulo; angulo <= 180; angulo++){
    servo.write(angulo);
    
    vet[angulo] = readDistance();

    Serial.println(vet[angulo]);
    tone(buzzer, 200/vet[angulo]); // Activate the buzzer at the frequency relative to C in Hz (Dó)
    delay(100);   // Wait for a while to deactivate 
    noTone(buzzer); //Deactivate the buzzer
  
  }

  for (int i = 0; i <= 180; i++) {
        if (vet[i] < menor) {
            menor = vet[i];
            indice = i;
        }
    }
  delay(100);
  servo.write(indice);
  
  Serial.print("menor valor ");
  Serial.println(menor);

  Serial.print("posicao em graus: ");
  Serial.println(indice);

  delay(10000);
}

void loop() {
  //distance = readDistance();
  //bool isNearby = distance < 50;
  //digitalWrite(LED_BUILTIN, isNearby);
  //delay(100);
  movimento();
  
}