
#include "Arduino.h"
#include "SensoresDeFaixa.h"

SensoresDeFaixa::SensoresDeFaixa() {
  sensor_esquerdo_extremo = SensorDeRefletancia(A1);
  sensor_esquerdo_centro  = SensorDeRefletancia(A2);
  sensor_frontal          = SensorDeRefletancia(A3);
  sensor_central          = SensorDeRefletancia(A4);
  sensor_direito_centro   = SensorDeRefletancia(A5);
  sensor_direito_extremo  = SensorDeRefletancia(A6);
}

void SensoresDeFaixa::configurarModo(byte modo) {
  modo = modo;
}

/**
 * Faz uma leitura nos sensores de faixa
 * retorno: a situação que os sensores estão enxergando
 */
byte SensoresDeFaixa::ler() {
  int see = sensor_esquerdo_extremo.ler();
  int sec = sensor_esquerdo_centro.ler();
  int sf  = sensor_frontal.ler();
  int sc  = sensor_central.ler();
  int sdc = sensor_direito_centro.ler();
  int sde = sensor_direito_extremo.ler();

  if (modo == 1) {
    if (sf > limite) {
      if (see > _limite and sde > _limite and sc > _limite and sec > _limite and sdc > _limite) {
        return CRUZAMENTO_TOTAL;
      }

      else if (see > limite and sde <= limite and sc > _limite and sec > _limite) {
        
        int see = sensor_esquerdo_extremo.ler();
        int sc  = sensor_central.ler();
        int sde = sensor_direito_centro.ler();

        if (see > limite and sc > limite and sde > limite) {
          return CRUZAMENTO_TOTAL;
        }

        return CRUZAMENTO_COM_PRETO_NA_ESQUERDA;
      }

      else if (sde > _limite and see <= limite and sc > _limite and sdc > _limite) {

        int see = sensor_esquerdo_extremo.ler();
        int sc  = sensor_central.ler();
        int sde = sensor_direito_centro.ler();

        if (see > limite and sc > limite and sde > limite) {
          return CRUZAMENTO_TOTAL;
        }

        return CRUZAMENTO_COM_PRETO_NA_DIREITA;
      }

      else if (sec > limite and see <= limite and sdc <= limite and sc > limite) {
        return CURVA_SIMPLES_PARA_A_ESQUERDA;
      }

      else if (sdc > limite and sde <= limite and sec <= limite and sc > limite) {
        return CURVA_SIMPLES_PARA_A_DIREITA;
      }

      else if (sdc <= limite and sec <= limite and sc > limite and see <= limite and sde <= limite) {
        return LINHA_RETA;
      }
    }
    else {
      if (see > _limite and sc > _limite and sde > _limite) {
        return CRUZAMENTO_T;
      }

      else if (see > limite and sde <= limite and sc > _limite and sec > _limite) {

        int see = sensor_esquerdo_extremo.ler();
        int sc  = sensor_central.ler();
        int sde = sensor_direito_centro.ler();

        if (see > limite and sc > limite and sde > limite) {
          return CRUZAMENTO_T;
        }

        return CURVA_DE_NOVENTA_GRAUS_PARA_A_ESQUERDA;
      }

      else if (sde > limite and see <= limite and sc > _limite and sdc > _limite) {
        
        int see = sensor_esquerdo_extremo.ler();
        int sc  = sensor_central.ler();
        int sde = sensor_direito_centro.ler();

        if (see > limite and sc > limite and sde > limite) {
          return CRUZAMENTO_T;
        }
        
        return CURVA_DE_NOVENTA_GRAUS_PARA_A_DIREITA;
      }

      else if (sc > limite and see <= limite and sde <= limite and sec <= limite and sdc <= limite) {
        return GAP;
      }

      else if (sc > limite and sec > limite and sdc <= limite and see <= limite and sde <= limite) {
        return CURVA_SIMPLES_PARA_A_ESQUERDA;
      }

      else if (sc > limite and sdc > limite and sec <= limite and see <= limite and sde <= limite) {
        return CURVA_SIMPLES_PARA_A_DIREITA;
      }

      else if (see > _limite and sc <= limite and sde <= limite and sdc <= limite) {
        return RETORNO_PARA_A_LINHA_PELA_DIREITA;
      }

      else if (sde > _limite and sc <= limite and see <= limite and sec <= limite) {
        return RETORNO_PARA_A_LINHA_PELA_ESQUERDA;
      }
    }
  }

  else if (modo == 2) {
    if (sc > limite and sec > limite and sdc <= limite) {
      return CURVA_SIMPLES_PARA_A_ESQUERDA;
    }

    else if (sc > limite and sdc > limite and sec <= limite) {
      return CURVA_SIMPLES_PARA_A_DIREITA;
    }

    else if (sf > limite and sdc <= limite and sec <= limite and sc > limite) {
      return LINHA_RETA;
    }

    else if (sc <= limite and sde <= limite and sdc <= limite) {
      return RETORNO_PARA_A_LINHA_PELA_DIREITA;
    }

    else if (sde > _limite and sc <= limite and see <= limite and sec <= limite) {
      return RETORNO_PARA_A_LINHA_PELA_ESQUERDA;
    }
  }

  return 0;
}

/**
 * Faz uma leitura no sensor de faixa frontal
 * retorno: um valor entre 0 e 1023
 */
int SensoresDeFaixa::lerSensorFrontal() {
  return sensor_frontal.ler();
}

/**
 * Faz uma leitura no sensor de faixa central
 * retorno: um valor entre 0 e 1023
 */
int SensoresDeFaixa::lerSensorCentral() {
  return sensor_central.ler();
}