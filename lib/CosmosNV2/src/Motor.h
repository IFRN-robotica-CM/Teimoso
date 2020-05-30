
#ifndef _Motor_h
#define _Motor_h

#include <Arduino.h>

// ------------------------------------- Classe Motor --------------------------------------- //

class Motor
{
  public:
    Motor();
    Motor(uint8_t porta);
    void configurarPonteH(uint8_t ponte_h);
    void configurarVelocidade(uint8_t velocidade);
    void girar(uint8_t sentido);
    void girar(uint8_t sentido, uint8_t velocidade);
    void parar();
  private:
    static boolean estado_dos_motores[8];
    int converterVelocidadeEmValorAnalogico(uint8_t velocidade);
    void atualizarCI74HC595();
    uint8_t _porta;
    uint8_t _ponte_h;
    uint8_t _velocidade;
};

#endif
