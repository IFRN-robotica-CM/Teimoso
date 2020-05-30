
#include <Arduino.h>
#include "SensorDeRefletancia.h"
#include "Constantes.h"

// ------------------------------- Classe SensorDeRefletancia ------------------------------------- //

SensorDeRefletancia::SensorDeRefletancia() {}

SensorDeRefletancia::SensorDeRefletancia(uint8_t pino) {
	_pino = pino;

	pinMode(_pino, INPUT);

	configurarModo(ANALOGICO);
}

int SensorDeRefletancia::ler() {
	return (_modo == ANALOGICO)?analogRead(_pino):digitalRead(_pino);
}

void SensorDeRefletancia::configurarModo(uint8_t modo) {
	_modo = modo;
}