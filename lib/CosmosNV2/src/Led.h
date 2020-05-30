
#ifndef _LED_H
#define _LED_H

#include <Arduino.h>

// ------------------------------------- Classe Led --------------------------------------- //

class Led
{
  public:
    Led(uint8_t porta);
    void acender();
    void apagar();
    void alternar();
    void inverter();
  private:
    uint8_t _porta;
    boolean invertido;
};

#endif