/*
                          SensorDeCor.ino

  Este código explica como utilizar sensores de cor na Cosmos NV2 Shield
  Criado em 27 de Março de 2020
  Por Vinícios Silva
*/

#include "CosmosNV2.h"   // Inclui a biblioteca

uint16_t r;              // Cria um variável do tipo uint16_t para guardar o valor do vermelho
uint16_t g;              // Cria um variável do tipo uint16_t para guardar o valor do verde
uint16_t b;              // Cria um variável do tipo uint16_t para guardar o valor do azul
uint16_t c;              // Cria um variável do tipo uint16_t para guardar o valor da claridade

SensorDeCor sensor(D);   // Cria um sensor de cor

void setup() {
  sensor.iniciar();      // Inicia o sensor
  Serial.begin(115200);  // Inicia o Monitor Serial com velocidade de transferência de 115200 bits/s
}

void loop() {
  sensor.obterValores(&r, &g, &b, &c); // Faz uma leitura no sensor e guarda nas variáveis

  Serial.print(r);       // Mostra os valores no Monitor Serial 
  Serial.print("   ");
  Serial.print(g);
  Serial.print("   ");
  Serial.print(b);
  Serial.print("   ");
  Serial.println(c);
}
