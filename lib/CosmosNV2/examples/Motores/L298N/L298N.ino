
/*
                          L298N.ino

  Este código explica como controlar motores na Cosmos NV2 Shield
  Criado em 27 de Março de 2020
  Por Vinícios Silva
*/

#include "CosmosNV2.h"            // Inclui a biblioteca

Motor motor(M1);                  // Cria um motor 

void setup() {
  motor.configurarPonteH(L298N);  // Configura o motor para ser controlado pela ponte h L298N
  motor.configurarVelocidade(80); // Configura a velocidade do motor para 80%
}

void loop() {
  motor.girar(PARA_FRENTE);       // Gira o motor para frente
  delay(2000);                    // Espera 2 segundos
  
  motor.girar(PARA_TRAS);         // Gira o motor para tras
  delay(2000);                    // Espera 2 segundos
}
