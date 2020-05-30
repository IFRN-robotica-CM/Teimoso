
#include <Arduino.h>
#include "Pinagem.h"
#include "Constantes.h"
#include "SensorDeDistancia.h"

#define ENDERECO_SENSOR_PORTA_L1 0x31
#define ENDERECO_SENSOR_PORTA_L2 0x32
#define ENDERECO_SENSOR_PORTA_L3 0x33
#define ENDERECO_SENSOR_PORTA_L4 0x34
#define ENDERECO_SENSOR_PORTA_L5 0x35
#define ENDERECO_SENSOR_PORTA_L6 0x36
#define ENDERECO_SENSOR_PORTA_L7 0x37

// ----------------------------- Classe SensorDeDistancia ----------------------------------- //

SensorDeDistancia::SensorDeDistancia() {}

SensorDeDistancia::SensorDeDistancia(uint8_t porta) {
	_porta = porta;

	switch (_porta) {
	case L1:
		shut = PINO_XSHUT_SENSOR_PORTA_L1;
		endereco = ENDERECO_SENSOR_PORTA_L1;
		break;
	case L2:
		shut = PINO_XSHUT_SENSOR_PORTA_L2;
		endereco = ENDERECO_SENSOR_PORTA_L2;
		break;
	case L3:
		shut = PINO_XSHUT_SENSOR_PORTA_L3;
		endereco = ENDERECO_SENSOR_PORTA_L3;
		break;
	case L4:
		shut = PINO_XSHUT_SENSOR_PORTA_L4;
		endereco = ENDERECO_SENSOR_PORTA_L4;
		break;
	case L5:
		shut = PINO_XSHUT_SENSOR_PORTA_L5;
		endereco = ENDERECO_SENSOR_PORTA_L5;
		break;
	case L6:
		shut = PINO_XSHUT_SENSOR_PORTA_L6;
		endereco = ENDERECO_SENSOR_PORTA_L6;
		break;
	case L7:
		shut = PINO_XSHUT_SENSOR_PORTA_L7;
		endereco = ENDERECO_SENSOR_PORTA_L7;
		break;
	default:
		break;
	}

	pinMode(shut, OUTPUT);
	digitalWrite(shut, LOW);
}

boolean SensorDeDistancia::iniciar() {
	digitalWrite(shut, HIGH);
  delay(10);

	return sensor.begin(endereco);
}

int SensorDeDistancia::ler() {
	sensor.rangingTest(&distancia);

  if (distancia.RangeStatus != 4) {
    return distancia.RangeMilliMeter/10;
  }
  return 819;
}
