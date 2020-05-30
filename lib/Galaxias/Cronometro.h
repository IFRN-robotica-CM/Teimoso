
#include <Arduino.h>

class Cronometro
{
  public:
    Cronometro();
    ~Cronometro();
    void configurarTempo(unsigned int ms);
    void iniciarContagem();
    bool finalizouContagem();
    unsigned int obtertempoRestante();
    unsigned int obterTempoDecorrido();
  private:
    unsigned long tempoDeInicio = 0, tempoDeTermino = 0;
    unsigned int intervalo = 0;
    bool contando = false;    
};