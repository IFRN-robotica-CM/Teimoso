#include <Arduino.h>
#include "Cronometro.h"

Cronometro::Cronometro() {}

Cronometro::~Cronometro() {}

void Cronometro::configurarTempo(unsigned int ms) {
  intervalo = ms;
}

void Cronometro::iniciarContagem() {
  contando = true;
  tempoDeInicio = millis();
  tempoDeTermino = tempoDeInicio + (unsigned long) intervalo;
}

bool Cronometro::finalizouContagem(){
  if (millis() >= tempoDeTermino) {
    contando = false;
  }

  if (contando) {
    return false;
  }

  return true;
}

unsigned int Cronometro::obterTempoDecorrido() {
  if (contando) {
    return (millis() - tempoDeInicio);
  }

  return intervalo;
}

unsigned int Cronometro::obtertempoRestante() {
  if (contando) {
    return (tempoDeTermino - millis());
  }

  return 0;
}