
#include <Arduino.h>
#include "ServoMotor.h"

// ----------------------------------- Classe ServoMotor ------------------------------------ //

ServoMotor::ServoMotor() {}

ServoMotor::ServoMotor(uint8_t porta) {
	servo.attach(porta);
}

void ServoMotor::anexar(uint8_t porta) {
	servo.attach(porta);
}

void ServoMotor::desanexar() {
	servo.detach();
}

void ServoMotor::gravar(uint8_t angulo) {
	servo.write(angulo);
}
