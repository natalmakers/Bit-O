#include <bito.h>
// ----------------------------------- BIBLIOTECAS
#include <SoftwareSerial.h>
#include <Ultrasonic.h>

// ----------------------------------- CONFIGURAÃ‡Ã•ES INICIAIS DO ULTRASSOM

#define TRIGGER_PIN  12 //Configura os pinos do Arduino usados para a aquisiÃ§Ã£o de dados do sensor
#define ECHO_PIN     13 //UltrassÃ´nico Trigger(11) e Echo(10)

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

// ----------------------------------- FIM - CONFIGURAÃ‡Ã•ES INICIAIS DO ULTRASSOM

// ----------------------------------- DEFINIÃ‡Ã•ES DE VARIÃVEIS GLOBAIS

String device;
boolean flag, obstaculo = false;

// ----------------------------------- FIM - DEFINIÃ‡Ã•ES DE VARIÃVEIS GLOBAIS


//DefiniÃ§Ãµes dos Pinos do Arduino ligados a entrada da Ponte H
int IN1 = 9; // MOTOR A-A
int IN2 = 8; // MOTOR A-B
int IN3 = 7; // MOTOR B-A
int IN4 = 6; // MOTOR B-B
byte vel1 = 11 , vel2 = 10;

void setup()
{
  flag = false;
  //Define os pinos ligados aos motores como SaÃ­das
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(vel1, OUTPUT);
  pinMode(vel2, OUTPUT);
  Serial.begin(9600);
}
//--------------------VARIÃVEIS GLOBAIS--------------------------

String tempo_aux = "";
long unsigned int tempo;
char tempo_aux2[10];
boolean flag_tempo = false;
float distancia_cm;

//--------------------/VARIÃVEIS GLOBAIS--------------------------

void loop() {
  digitalWrite(vel1, 1);
  digitalWrite(vel2, 1);
  float distancia_cm;
  long tempo_ms = ultrasonic.timing();
  distancia_cm = ultrasonic.convert(tempo_ms, Ultrasonic::CM);

  if (distancia_cm >= 300) {
    distancia_cm = 300;
  }
  if (distancia_cm <= 10)
  {
    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
    distancia_cm = ultrasonic.convert(tempo_ms, Ultrasonic::CM);
  }

  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);

  Serial.print("Valor de distancia: ");
  Serial.println(distancia_cm);

  // Caso a distÃ¢ncia (distancia_cm) for menor que 20cm e flag for verdadeira(flag indica que botÃ£o foi pressionado)
  // ou caso a distÃ¢ncia (distancia_cm) for menor que 20cm e encontrar um obstaculo entra no IF
  if (((distancia_cm < 20.00)) || ((distancia_cm < 20.00) && obstaculo)) {
    Serial.println("Entrou no IF do Obstaculo.");
    melhor_lado();
    digitalWrite(IN1, 1);
    digitalWrite(IN2, 0);
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
    flag = !flag;
    obstaculo = true;
  }
  delay(100);
}

// FunÃ§Ã£o que escolhe o melhor lado para o Bit-O seguir baseado na comparaÃ§Ã£o de distÃ¢ncias lidas ao en-
// contrar um obstÃ¡culo. O lado (esquerda ou direita) com a maior distÃ¢ncia para um novo obstÃ¡culo Ã©
// usada para seguir com o comando anteriormente enviado.

void melhor_lado() {
  float distancia_direita1, distancia_direita2, media_direita, distancia_esquerda1, distancia_esquerda2, media_esquerda;

  //Gira para a Direita
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(400);
  long tempo_ms1 = ultrasonic.timing();
  delay(50);
  long tempo_ms2 = ultrasonic.timing();
  delay(50);
  //Armazena a primeira mediÃ§Ã£o da distÃ¢ncia para o prÃ³ximo obstÃ¡culo Ã  direita
  distancia_direita1 = ultrasonic.convert(tempo_ms1, Ultrasonic::CM);
  //Armazena a segunda mediÃ§Ã£o da distÃ¢ncia para o prÃ³ximo obstÃ¡culo Ã  direita
  distancia_direita2 = ultrasonic.convert(tempo_ms2, Ultrasonic::CM);
  // Calcula a media da distÃ¢ncia Ã  direita, a fim de minimizar erros de leituras
  media_direita = (distancia_direita1 + distancia_direita2) / 2;

  //Gira para a Esquerda + Distancia da direita para o Centro
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(400);
  //Armazena a primeira mediÃ§Ã£o da distÃ¢ncia para o prÃ³ximo obstÃ¡culo Ã  esquerda
  distancia_esquerda1 = ultrasonic.convert(tempo_ms1, Ultrasonic::CM);
  //Armazena a segunda mediÃ§Ã£o da distÃ¢ncia para o prÃ³ximo obstÃ¡culo Ã  esquerda
  distancia_esquerda2 = ultrasonic.convert(tempo_ms2, Ultrasonic::CM);
  // Calcula a media da distÃ¢ncia Ã  esquerda, a fim de minimizar erros de leituras
  media_esquerda = (distancia_esquerda1 + distancia_esquerda2) / 2;

  //Compara as medias
  if (media_direita > media_esquerda) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(400);
  }
  else if (media_esquerda > media_direita){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(400);
  }
}
