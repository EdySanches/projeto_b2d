// INCLUSÃO DE BIBLIOTECAS
#include <MPU6050_tockn.h>
#include <Wire.h>

//DEFINIÇÕES
#define MPU6050_ADDR         0x68 // ENDEREÇO QUANDO O PINO AD0 ESTIVER LIGADO AO GND
#define pinMot1A 13
#define pinMot1B 11

#define velocidade 5
#define DEBUG

int duracaoPulso = 5;   //duracao em milisegundos de acionamento do motor
int intervalo = 40;     //intervalo em milisegundos entre os acionamentos
int tolerancia = 2;     //tolerancia em graus da rotacao da plataforma

// INSTANCIANDO OBJETOS
MPU6050 mpu6050(Wire);

// DECLARAÇÃO DE VARIÁVEIS  
float angulo;

unsigned long controleTempo;

void setup() {

  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  
  Serial.begin(9600);
  Serial.println("CONFIGURANDO");

  pinMode(pinMot1A, OUTPUT);
  pinMode(pinMot1B, OUTPUT);  
  pinMode(3, OUTPUT);
  analogWrite(3, velocidade);
  
  #ifdef DEBUG
    Serial.println("Fim Setup");
  #endif
}

void loop() {
  for(;;){
    mpu6050.update();

    angulo = mpu6050.getAngleY();
    
    Serial.print("angulo : ");
    Serial.print(angulo);
    
    if((angulo>=(tolerancia+2))){
        delay(intervalo);

        digitalWrite(pinMot1B, HIGH);
        delay(duracaoPulso);
        digitalWrite(pinMot1B, LOW);
    }
    
    if((angulo<=((tolerancia-1)*-2))){
        delay(intervalo);

        digitalWrite(pinMot1A, HIGH);
        delay(duracaoPulso);
        digitalWrite(pinMot1A, LOW);
    }
  }
  

  
}
