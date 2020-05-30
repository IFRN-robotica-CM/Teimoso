/*
                          ServoMotor.ino
  Este código explica como utilizar servos motores na Cosmos NV2 Shield
  Criado em 27 de Março de 2020
  Por Vinícios Silva
*/

#include "CosmosNV2.h"            // Inclui a biblioteca

Tela tela;                        // Cria a tela

void setup() {
  tela.iniciar();                 // Habilita a tela da placa
  tela.limpar();                  // Limpa a tela
  tela.configurarCursor(10, 20);  // Configura o cursor para posição (10,20)
  tela.escrever("Ola Mundo");     // Escreve "Ola mundo"
  tela.mostrar();                 // Mostra na tela
}

void loop() {
  
}
