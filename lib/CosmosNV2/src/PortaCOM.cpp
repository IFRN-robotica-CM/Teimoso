
#include <Arduino.h>
#include "PortaCOM.h"

// ------------------------------------ Classe PortaCOM ------------------------------------- //

PortaCOM::PortaCOM() {}

void PortaCOM::iniciar(long velocidade) {
  meu_serial.begin(velocidade);
}

boolean PortaCOM::existeDadoDisponivel() {
  return (meu_serial.available() > 0)?true:false;
}

int PortaCOM::ler() {
  return meu_serial.read();
}

void PortaCOM::enviar(char caractere) {
  meu_serial.write(caractere);
}



