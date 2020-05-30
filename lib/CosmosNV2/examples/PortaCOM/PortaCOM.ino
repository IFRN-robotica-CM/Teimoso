/*
                          PortaCOM.ino

  Este código explica como utilizar a porta de comunicação serial da Cosmos NV2 Shield
  Criado em 27 de Março de 2020
  Por Vinícios Silva
*/

#include "CosmosNV2.h"      // Inclui a biblioteca

PortaCOM portaCOM;          // Cria e habilita a porta de comunicação da placa 

void setup() {
  portaCOM.iniciar(115200); // inicia a comunicação com a velocidade de tranferência de 115200 bits/s
  portaCOM.enviar('V');     // Envia um 'V' pela porta
}

void loop() {
  
}