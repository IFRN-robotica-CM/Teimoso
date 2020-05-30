
#ifndef _PortaCOM_h
#define _PortaCOM_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Pinagem.h"

// ------------------------------------ Classe PortaCOM ------------------------------------- //

class PortaCOM
{
  public:
    PortaCOM();
    void iniciar(long velocidade);
    boolean existeDadoDisponivel();
    int ler();
    void enviar(char caractere);
  private:
    SoftwareSerial meu_serial = SoftwareSerial(PINO_RX, PINO_TX);
};

#endif
