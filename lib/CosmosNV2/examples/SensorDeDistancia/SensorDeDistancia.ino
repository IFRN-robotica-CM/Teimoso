/*
                          SensorDeDistancia.ino

  Este código explica como utilizar sensores de distancia na Cosmos NV2 Shield
  Criado em 27 de Março de 2020
  Por Vinícios Silva
*/

#include "CosmosNV2.h"        // Inclui a biblioteca

int distancia = 0;            // Cria uma variável inteira para guardar a distância

SensorDeDistancia sensor(L1); // Cria um sensor de distância e anexa ele a porta L1

void setup() {
  sensor.iniciar();           // Iniciar o sensor
  Serial.begin(115200);       // Inicia o Monitor Serial com velocidade de transferência de 115200 bits/s
}

void loop() {
  distancia = sensor.ler();   // Faz uma leitura no sensor e guarda o resultado na variável distância

  Serial.print("Distância: ");// Mostra os dados no Monitor Serial
  Serial.println(distancia);

  delay(500);                 // Espera 500ms
}
