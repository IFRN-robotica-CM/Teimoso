
#ifndef _SensorDeDistancia_h
#define _SensorDeDistancia_h

#include <Arduino.h>
#include "Adafruit_VL53L0X.h"

// ----------------------------- Classe SensorDeDistancia ----------------------------------- //

class SensorDeDistancia
{
  public:
    SensorDeDistancia();
    SensorDeDistancia(uint8_t porta);
    boolean iniciar();
    int ler();
  private:
    uint8_t _porta, shut, endereco;
    Adafruit_VL53L0X sensor;
    VL53L0X_RangingMeasurementData_t distancia;
};

#endif
