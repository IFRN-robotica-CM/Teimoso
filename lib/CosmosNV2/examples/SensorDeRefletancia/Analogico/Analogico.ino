/*
                          Analogico.ino

  Este código explica como utilizar sensores de refletancia na Cosmos NV2 Shield
  Criado em 27 de Março de 2020
  Por Vinícios Silva
*/

#include "CosmosNV2.h"              // Inclui a biblioteca

int valor_lido = 0;                 // Cria uma variável inteira

SensorDeRefletancia sensor(A1);     // Cria um sensor de refletância e anexa ele na porta A1

void setup() {
  sensor.configurarModo(ANALOGICO); // Configura o sensor como sensor analogico
  Serial.begin(115200);             // Inicia o Monitor Serial com velocidade de transferência de 115200 bits/s
}

void loop() {
  valor_lido = sensor.ler();        // Faz uma leitura no sensor e guarda o resultado na variável valor_lido

  Serial.print("Valor: ");          // Mostra os dados no Monitor Serial
  Serial.println(valor_lido);

  delay(500);                       // Espera 500ms
}