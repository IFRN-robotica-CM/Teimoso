
#include <Arduino.h>
#include "Motor.h"
#include "Pinagem.h"
#include "Constantes.h"

// ------------------------------------- Classe Motor --------------------------------------- //

boolean Motor::estado_dos_motores[8] = {0, 0, 0, 0, 0, 0, 0, 0};

Motor::Motor() {}

Motor::Motor(uint8_t porta) {
  _porta = porta;
}

void Motor::configurarPonteH(uint8_t ponte_h) {
  _ponte_h = ponte_h;

  if (_ponte_h == L298N) {
    switch (_porta) {
      case M1:
        pinMode(PINO_MOTOR_1A_L298N, OUTPUT);
        pinMode(PINO_MOTOR_1B_L298N, OUTPUT);
        pinMode(PINO_VELOCIDADE_MOTOR_1_L298N, OUTPUT);
        break;
      case M2:
        pinMode(PINO_MOTOR_2A_L298N, OUTPUT);
        pinMode(PINO_MOTOR_2B_L298N, OUTPUT);
        pinMode(PINO_VELOCIDADE_MOTOR_2_L298N, OUTPUT);
        break;
      default:
      break;
    }
  }

  else if (_ponte_h == L293D) {
    for (int i = 7; i >= 0; i--) {
      estado_dos_motores[i] = 0; 
    }
    
    pinMode(PINO_LATCH, OUTPUT);
    pinMode(PINO_CLOCK, OUTPUT);
    pinMode(PINO_DATA, OUTPUT);
    pinMode(PINO_ENABLE, OUTPUT);

    digitalWrite(PINO_ENABLE, LOW);

    switch (_porta) {
      case M1:
        pinMode(PINO_VELOCIDADE_MOTOR_1_L293D, OUTPUT);
        break;
      case M2:
        pinMode(PINO_VELOCIDADE_MOTOR_2_L293D, OUTPUT);
        break;
      case M3:
        pinMode(PINO_VELOCIDADE_MOTOR_3_L293D, OUTPUT);
        break;
      case M4:
        pinMode(PINO_VELOCIDADE_MOTOR_4_L293D, OUTPUT);
        break;
      default:
      break;
    }

    atualizarCI74HC595();
  }
}

// Converte uma velocidade entre 0 e 100 em um valor entre 0 e 255
int Motor::converterVelocidadeEmValorAnalogico(uint8_t velocidade) {
  return ((int) ceil(velocidade*0.01*255));
}

void Motor::configurarVelocidade(uint8_t velocidade) {

  uint8_t pino_pwm;

  if (_ponte_h == L298N) {
    switch (_porta) {
      case M1:
        pino_pwm = PINO_VELOCIDADE_MOTOR_1_L298N;
        break;
      case M2:
        pino_pwm = PINO_VELOCIDADE_MOTOR_2_L298N;
        break;
      default:
      break;
    }

    analogWrite(pino_pwm, converterVelocidadeEmValorAnalogico(velocidade));
  }

  else if (_ponte_h == L293D) {
    switch (_porta) {
      case M1:
        pino_pwm = PINO_VELOCIDADE_MOTOR_1_L293D;
        break;
      case M2:
        pino_pwm = PINO_VELOCIDADE_MOTOR_2_L293D;
        break;
      case M3:
        pino_pwm = PINO_VELOCIDADE_MOTOR_3_L293D;
        break;
      case M4:
        pino_pwm = PINO_VELOCIDADE_MOTOR_4_L293D;
        break;
      default:
      break;
    }

    analogWrite(pino_pwm, converterVelocidadeEmValorAnalogico(velocidade));
  }
}

void Motor::atualizarCI74HC595() {
  digitalWrite(PINO_LATCH, LOW);

  for (int i = 7; i >= 0; i--) {
    digitalWrite(PINO_CLOCK, LOW);
    digitalWrite(PINO_DATA, estado_dos_motores[i]);
    digitalWrite(PINO_CLOCK, HIGH);
    digitalWrite(PINO_DATA, LOW);
  }

  digitalWrite(PINO_LATCH, HIGH);
}

void Motor::girar(uint8_t sentido) {
  uint8_t a, b;

  if (_ponte_h == L298N) {
    switch (_porta) {
      case M1:
        a = PINO_MOTOR_1A_L298N; b = PINO_MOTOR_1B_L298N;
        break;
      case M2:
        a = PINO_MOTOR_2A_L298N; b = PINO_MOTOR_2B_L298N;
        break;
      default:
        return;
    }

    switch (sentido) {
      case PARA_FRENTE:
        digitalWrite(a, HIGH);
        digitalWrite(b, LOW);
        break;
      case PARA_TRAS:
        digitalWrite(a, LOW);
        digitalWrite(b, HIGH);
        break;
      default:
        break;
    }
  }

  else if (_ponte_h == L293D) {

    switch (_porta) {
      case M1:
        a = PINO_CI_74HC595_MOTOR_1A; b = PINO_CI_74HC595_MOTOR_1B;
        break;
      case M2:
        a = PINO_CI_74HC595_MOTOR_2A; b = PINO_CI_74HC595_MOTOR_2B;
        break;
      case M3:
        a = PINO_CI_74HC595_MOTOR_3A; b = PINO_CI_74HC595_MOTOR_3B;
        break;
      case M4:
        a = PINO_CI_74HC595_MOTOR_4A; b = PINO_CI_74HC595_MOTOR_4B;
        break;
      default:
        break;
    }

    switch (sentido) {
      case PARA_FRENTE:
        estado_dos_motores[a] = HIGH;
        estado_dos_motores[b] = LOW;
        break;
      case PARA_TRAS:
        estado_dos_motores[a] = LOW;
        estado_dos_motores[b] = HIGH;
        break;
      default:
        break;
    }
    
    atualizarCI74HC595();
  }
}

void Motor::girar(uint8_t sentido, uint8_t velocidade) {
  girar(sentido);
  configurarVelocidade(velocidade);
}

void Motor::parar() {
  uint8_t a, b;

	if (_ponte_h == L298N) {
    switch (_porta) {
      case 1:
        a = PINO_MOTOR_1A_L298N; b = PINO_MOTOR_1B_L298N;
        break;
      case 2:
        a = PINO_MOTOR_2A_L298N; b = PINO_MOTOR_2B_L298N;
        break;
      default:
        return;
    }

    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
  }

  else if (_ponte_h == L293D) {
    switch (_porta) {
      case M1:
        a = PINO_CI_74HC595_MOTOR_1A; b = PINO_CI_74HC595_MOTOR_1B;
        break;
      case M2:
        a = PINO_CI_74HC595_MOTOR_2A; b = PINO_CI_74HC595_MOTOR_2B;
        break;
      case M3:
        a = PINO_CI_74HC595_MOTOR_3A; b = PINO_CI_74HC595_MOTOR_3B;
        break;
      case M4:
        a = PINO_CI_74HC595_MOTOR_4A; b = PINO_CI_74HC595_MOTOR_4B;
        break;
      default:
        break;
    }

    estado_dos_motores[a] = LOW;
    estado_dos_motores[b] = LOW;

    atualizarCI74HC595();
  }
}
