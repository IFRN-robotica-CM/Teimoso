/*
                          L293D.ino

  Este código explica como utilizar leds na Cosmos NV2 Shield
  Criado em 12 de Abril 2020
  Por Vinícios Silva
*/

#include "CosmosNV2.h"  // Inclui a biblioteca

Led led(13);            // Cria um led e anexa-o na porta 13

void setup() {
  
}

void loop() {
  led.acender();        // Acende o led
  delay(1000);          // espera 1 segundo
  
  led.apagar();         // Apaga o led
  delay(1000);          // espera 1 segundo
}