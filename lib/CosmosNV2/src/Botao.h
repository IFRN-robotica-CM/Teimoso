
#ifndef _BOTAO_H
#define _BOTAO_H

#include <Arduino.h>
#include "CosmosNV2.h"

// ------------------------------------- Classe Botao --------------------------------------- //

class Botao: public SensorDeToque {
  public :
    Botao(uint8_t porta);
};

#endif
