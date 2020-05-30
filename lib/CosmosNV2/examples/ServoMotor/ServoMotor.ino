/*
                          ServoMotor.ino
  Este código explica como utilizar servos motores na Cosmos NV2 Shield
  Criado em 27 de Março de 2020
  Por Vinícios Silva
*/

#include "CosmosNV2.h"          // Inclui a biblioteca

ServoMotor servo(S1);           // Cria um servo e anexa ele na porta S1

void setup() {
}

void loop() {
  servo.gravar(0);              // Faz o servo ir para o ângulo 0
  delay(1000);                  // Espera 1000ms
  
  servo.gravar(180);            // Faz o servo ir para o ângulo 180
  delay(1000);                  // Espera 1000ms
}
