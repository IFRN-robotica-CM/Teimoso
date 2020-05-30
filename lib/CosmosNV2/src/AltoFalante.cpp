
#include <Arduino.h>
#include "Pinagem.h"
#include "AltoFalante.h"

// ------------------------------------- Alto Falante --------------------------------------- //

AltoFalante::AltoFalante() {
  pinMode(PINO_ALTO_FALANTE, OUTPUT);
}

void AltoFalante::tocar(unsigned int frequencia) {
  tone(PINO_ALTO_FALANTE, frequencia);
}

void AltoFalante::parar() {
  noTone(PINO_ALTO_FALANTE);
}

void AltoFalante::bipar(uint8_t quantidade_de_vezes, unsigned int frequencia) {
  for (int i = 0; i < quantidade_de_vezes; i++) {
    tocar(frequencia);
    delay(200);
    parar();
  }
}
