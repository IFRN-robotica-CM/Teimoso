
#ifndef Galaxias_h
#define Galaxias_h

#include "Cabecalhos.h"
#include "Motor.h"
#include "SensoresDeFaixa.h"
#include "Cronometro.h"

Cronometro cronometro_1;

SensoresDeFaixa sensoresDeFaixa;

SensorDeToque sensorToqueFrontal(B);

SensorDeDistancia sensorDistanciaEsquerdo (L1);
SensorDeDistancia sensorDistanciaDireito  (L2);

Botao botaoStart(23);
Botao botaoClear(25);

Motor motorDireito  (M1);
Motor motorEsquerdo (M2);

#define esperar delay

#endif
