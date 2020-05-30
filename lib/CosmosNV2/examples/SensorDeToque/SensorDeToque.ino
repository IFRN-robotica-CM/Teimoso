/*
                          SensorDeToque.ino

  Este código explica como utilizar sensores de toque na Cosmos NV2 Shield
  Criado em 27 de Março de 2020
  Por Vinícios Silva
*/

#include "CosmosNV2.h"              // Inclui a biblioteca

int valor_lido = 0;                 // Cria uma variável inteira

SensorDeToque sensor(B);            // Cria um sensor de toque e anexa ele na porta B

void setup() {
  Serial.begin(115200);             // Inicia o Monitor Serial com velocidade de transferência de 115200 bits/s
}

void loop() {
  valor_lido = sensor.lerEstado();  // Faz uma leitura no sensor e guarda o resultado na variável valor_lido

  Serial.print("Valor: ");          // Mostra os dados no Monitor Serial
  Serial.println(valor_lido);

  delay(500);                       // Espera 500ms
}
