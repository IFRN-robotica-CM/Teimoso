
#include <Arduino.h>
#include "SensorDeToque.h"

// -------------------------------- Classe SensorDeToque ------------------------------------ //

SensorDeToque::SensorDeToque() {}

SensorDeToque::SensorDeToque(uint8_t porta) {
	_porta = porta;
	pinMode(_porta, INPUT_PULLUP);
}

boolean SensorDeToque::lerEstado() {
	return !digitalRead(_porta);
}
