
#include "Arduino.h"
#include "CosmosNV2.h"

#define CRUZAMENTO_TOTAL                         1
#define CRUZAMENTO_COM_PRETO_NA_ESQUERDA         2
#define CRUZAMENTO_COM_PRETO_NA_DIREITA          3
#define CRUZAMENTO_T                             4
#define CURVA_DE_NOVENTA_GRAUS_PARA_A_ESQUERDA   5
#define CURVA_DE_NOVENTA_GRAUS_PARA_A_DIREITA    6
#define CURVA_SIMPLES_PARA_A_ESQUERDA            7
#define CURVA_SIMPLES_PARA_A_DIREITA             8
#define GAP                                      9
#define LINHA_RETA                               10
#define RETORNO_PARA_A_LINHA_PELA_ESQUERDA       11
#define RETORNO_PARA_A_LINHA_PELA_DIREITA        12

class SensoresDeFaixa {
  public:
    SensoresDeFaixa();
    void configurarModo(byte modo);
    byte ler();
    int lerSensorFrontal();
    int lerSensorCentral();
  
  private:
    byte modo;
    const int  limite = 500;
    const int _limite = 150;

    SensorDeRefletancia sensor_esquerdo_extremo;
    SensorDeRefletancia sensor_esquerdo_centro;
    SensorDeRefletancia sensor_frontal;
    SensorDeRefletancia sensor_central;
    SensorDeRefletancia sensor_direito_centro;
    SensorDeRefletancia sensor_direito_extremo;
};
