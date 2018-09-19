#include <bito.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); // RX, TX

char control;

byte in1 = 9;
byte in2 = 8;
byte in3 = 7;
byte in4 = 6;
byte vel1 = 11 , vel2 = 10;

unsigned long time_1 = 0;
int velocidade;


void setup() {
  // Open serial communications and wait for port to open:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(vel1, OUTPUT);
  pinMode(vel2, OUTPUT);
  Serial.begin(9600);

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("SetUp");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  //velocidade padrão
  velocidade = 255;

}

void loop() { // run over and over
  analogWrite(vel1, velocidade);
  analogWrite(vel2, velocidade);
  
  if (mySerial.available()) {
    control = mySerial.read();
    Serial.println(control);
    bito(control);
    time_1 = millis();

  }
  if (millis() - time_1 > 100) {

    digitalWrite(in1, 0);
    digitalWrite(in2, 0);
    digitalWrite(in3, 0);
    digitalWrite(in4, 0);

  }

}

void bito(char crt) {

  if (crt == 'a') {
    Serial.println("frente");
    digitalWrite(in1, 0);
    digitalWrite(in2, 1);
    digitalWrite(in3, 1);
    digitalWrite(in4, 0);

  }
  if (crt == 'b') {
    Serial.println("direita");
    digitalWrite(in1, 0);
    digitalWrite(in2, 1);
    digitalWrite(in3, 0);
    digitalWrite(in4, 1);

  }
  if (crt == 'c') {
    Serial.println("ré");

    digitalWrite(in1, 1);
    digitalWrite(in2, 0);
    digitalWrite(in3, 0);
    digitalWrite(in4, 1);

  }
  if (crt == 'd') {
    Serial.println("esquerda");

    digitalWrite(in1, 1);
    digitalWrite(in2, 0);
    digitalWrite(in3, 1);
    digitalWrite(in4, 0);

  }
  if (crt == 'e') {

    for (int i = 0; i < 2; i++) {

      digitalWrite(vel1, 1);
      digitalWrite(vel2, 1);

      digitalWrite(in1, 1);
      digitalWrite(in2, 0);
      digitalWrite(in3, 1);
      digitalWrite(in4, 0);
      delay(100);
      digitalWrite(in1, 0);
      digitalWrite(in2, 1);
      digitalWrite(in3, 0);
      digitalWrite(in4, 1);
      delay(100);
      analogWrite(vel1, velocidade);
      analogWrite(vel2, velocidade);
    }

  }
  if (crt == 'f') {
    velocidade += 1;
    if (velocidade > 254) {
      velocidade = 255;
    }
    Serial.println(velocidade);


  }
  if (crt == 'g') {


  }
  if (crt == 'h') {
    velocidade -= 1;
    if (velocidade < 20) {
      velocidade = 20 ;
    }
    Serial.println(velocidade);


  }

}

