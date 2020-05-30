/*
                          Bipes.ino
  Este código explica como utilizar o alto falante na Cosmos NV2 Shield
  Criado em 27 de Março de 2020
  Por Vinícios Silva
*/

#include "CosmosNV2.h"        // Inclui a biblioteca

AltoFalante altoFalante;      // Cria o alto falante 

void setup() {
  altoFalante.tocar(500);     // Faz o alto falante tocar na frequência de 500hz
  delay(100);                 // Espera 100ms
  altoFalante.parar();        // Faz o alto falante parar de tocar
  
  altoFalante.bipar(4, 800);  // Faz o alto falante bipar 4 vezes na frequencia de 800hz
}

void loop() {
  altoFalante.bipar(1, 1000); // Faz o alto falante bipar 1 vez na frequencia de 1000hz
}