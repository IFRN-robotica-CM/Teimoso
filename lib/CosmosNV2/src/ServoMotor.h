
#ifndef _ServoMotor_h
#define _ServoMotor_h

#include <Arduino.h>
#include <Servo.h>

// ----------------------------------- Classe ServoMotor ------------------------------------ //

class ServoMotor
{
  public:
    ServoMotor();
    ServoMotor(uint8_t porta);
    void anexar(uint8_t porta);
    void desanexar();
    void gravar(uint8_t angulo);
  private:
    Servo servo;
};

#endif
