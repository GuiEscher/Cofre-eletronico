#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Definindo os pinos do servo e do teclado
#define PINO_SERVO 6
#define LINHAS 4
#define COLUNAS 4

// Definindo a senha
String SENHA = "1234";

// Configuração do display LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Configuração do teclado matricial
char teclas[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Objeto do servo motor
Servo servo;

bool caixaTravada = true;
bool mudasenha = false;
String senhaDigitada = "";
byte pinosLinhas[LINHAS] = {9, 8, 7, A3};
byte pinosColunas[COLUNAS] = {5, 4, 3, 2};
Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);


void setup() {
  // Inicialização do display LCD
  lcd.init();
  lcd.backlight();

  // Inicialização do servo motor
  servo.attach(PINO_SERVO);
  servo.write(0); // Fecha a caixa inicialmente

  // Mensagem de boas-vindas no LCD
  lcd.setCursor(0, 1);
  lcd.print("Cofre Seguro");
  lcd.setCursor(0, 0);
  lcd.print("Bem vindo amigo!");
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Digite a Senha:");
  lcd.setCursor(0, 1);
  lcd.print("Confirme com #");
}

void loop() {
  char tecla = teclado.getKey();
  if (tecla) {
    if (tecla == '#') {
      // Verifica se a senha está correta
      if (senhaDigitada == SENHA) {
        if (caixaTravada) {
          // Destravar caixa
          servo.write(90); // Abre a caixa
          caixaTravada = false;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Cofre Seguro");
          lcd.setCursor(0, 1);
          lcd.print("Cofre Destravado");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Nova senha: *");
          lcd.setCursor(0, 1);
          lcd.print("Travar cofre: #");
          
        } else {
          // Travar caixa
          senhaDigitada = "";
          servo.write(0); // Fecha a caixa
          caixaTravada = true;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Cofre Seguro");
          lcd.setCursor(0, 1);
          lcd.print("Cofre Travado");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Digite a Senha:");
          lcd.setCursor(0, 1);
          lcd.print("Confirme com #");
        }
      } else {
        // Senha incorreta, limpa a entrada
        senhaDigitada = "";
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Cofre Seguro");
        lcd.setCursor(0, 1);
        lcd.print("Senha Incorreta!");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Digite a Senha:");
        lcd.setCursor(0, 1);
        lcd.print("Confirme com #");
      }
    } else if (tecla == '*'){
 
      if (caixaTravada == false){
          mudasenha = true;
          // Cria nova senha 
          senhaDigitada = "";
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Nova Senha:");
          lcd.setCursor(0, 1);
          lcd.print("A para confirmar");
      }
    }
    else if (tecla == 'A'){
      if (mudasenha == true){
        SENHA = senhaDigitada;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Senha Alterada!");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("# para sair");
        lcd.setCursor(0, 1);
        lcd.print("e fechar o cofre");
        mudasenha = false;
      }
    }
    else {
      // Adiciona o caractere digitado à senha
      senhaDigitada += tecla;
      lcd.setCursor(0, 1);
      lcd.print("[");
      lcd.setCursor(senhaDigitada.length(), 1);
      lcd.print("*");
      lcd.setCursor(senhaDigitada.length()+1, 1);
      lcd.print("]");
    }
  }
}