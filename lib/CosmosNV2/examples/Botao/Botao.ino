/*
                          Botao.ino
  Este código explica como utilizar botoes com esta biblioteca
  Criado em 12 de Abril de 2020
  Por Vinícios Silva
*/

#include "CosmosNV2.h"                  // Inclui a biblioteca

Botao botao(5);                         // Cria um botao e anexa na porta 5

void setup() {
  Serial.begin(9600);                   // Inicia a comunicação serial
}

void loop() {
  boolean estado = botao.lerEstado();   // Faz uma leitura no botao e guarda o resultado na variável "estado" 
  Serial.println(estado);               // Mostra o valor da variável "estado" no Monitor Serial
  delay(500);                           // Espera 500ms 
}