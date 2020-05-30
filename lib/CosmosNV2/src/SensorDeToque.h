
#ifndef _SensorDeToque_h
#define _SensorDeToque_h

#include <Arduino.h>

// -------------------------------- Classe SensorDeToque ------------------------------------ //

class SensorDeToque
{
  public:
    SensorDeToque();
    SensorDeToque(uint8_t porta);
    boolean lerEstado();
  private:
    uint8_t _porta;
};

#endif
