
#include <Arduino.h>
#include "Led.h"

// Construtor
Led::Led(uint8_t porta) {
  _porta = porta;
  invertido = false;
  pinMode(_porta, OUTPUT);
}

// Acende o led
void Led::acender() {
  if (!invertido) {
    digitalWrite(_porta, HIGH);
  }
  else {
    digitalWrite(_porta, LOW);
  }
}

// Apaga o led
void Led::apagar() {
  if (!invertido) {
    digitalWrite(_porta, LOW);
  }
  else {
    digitalWrite(_porta, HIGH);
  }
}

// Troca o estado do led
void Led::alternar() {
  digitalWrite(_porta, !digitalRead(_porta));
}

// Configura o led para funcionar com lógica invertida
void Led::inverter() {
  invertido = true;
}
