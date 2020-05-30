
#ifndef _AltoFalante_h
#define _AltoFalante_h

#include <Arduino.h>

// ------------------------------------- Alto Falante --------------------------------------- //

class AltoFalante
{
  public:
    AltoFalante();
    void tocar(unsigned int frequencia);
    void parar();
    void bipar(uint8_t quantidade_de_vezes, unsigned int frequencia);
};

#endif
