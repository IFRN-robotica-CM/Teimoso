
#include <Arduino.h>
#include "SensorDeCor.h"
#include "Constantes.h"
#include "Pinagem.h"

#define TCS34725_ADDRESS          (0x29)

#define TCS34725_COMMAND_BIT      (0x80)

#define TCS34725_ENABLE           (0x00)
// #define TCS34725_ENABLE_AIEN      (0x10)    /* RGBC Interrupt Enable */
#define TCS34725_ENABLE_WEN       (0x08)    /* Wait enable - Writing 1 activates the wait timer */
#define TCS34725_ENABLE_AEN       (0x02)    /* RGBC Enable - Writing 1 actives the ADC, 0 disables it */
#define TCS34725_ENABLE_PON       (0x01)    /* Power on - Writing 1 activates the internal oscillator, 0 disables it */
#define TCS34725_ATIME            (0x01)    /* Integration time */
#define TCS34725_WTIME            (0x03)    /* Wait time (if TCS34725_ENABLE_WEN is asserted) */
// #define TCS34725_WTIME_2_4MS      (0xFF)    /* WLONG0 = 2.4ms   WLONG1 = 0.029s */
// #define TCS34725_WTIME_204MS      (0xAB)    /* WLONG0 = 204ms   WLONG1 = 2.45s  */
// #define TCS34725_WTIME_614MS      (0x00)    /* WLONG0 = 614ms   WLONG1 = 7.4s   */
// #define TCS34725_AILTL            (0x04)    /* Clear channel lower interrupt threshold */
// #define TCS34725_AILTH            (0x05)
// #define TCS34725_AIHTL            (0x06)    /* Clear channel upper interrupt threshold */
// #define TCS34725_AIHTH            (0x07)
// #define TCS34725_PERS             (0x0C)    /* Persistence register - basic SW filtering mechanism for interrupts */
// #define TCS34725_PERS_NONE        (0b0000)  /* Every RGBC cycle generates an interrupt                                */
// #define TCS34725_PERS_1_CYCLE     (0b0001)  /* 1 clean channel value outside threshold range generates an interrupt   */
// #define TCS34725_PERS_2_CYCLE     (0b0010)  /* 2 clean channel values outside threshold range generates an interrupt  */
// #define TCS34725_PERS_3_CYCLE     (0b0011)  /* 3 clean channel values outside threshold range generates an interrupt  */
// #define TCS34725_PERS_5_CYCLE     (0b0100)  /* 5 clean channel values outside threshold range generates an interrupt  */
// #define TCS34725_PERS_10_CYCLE    (0b0101)  /* 10 clean channel values outside threshold range generates an interrupt */
// #define TCS34725_PERS_15_CYCLE    (0b0110)  /* 15 clean channel values outside threshold range generates an interrupt */
// #define TCS34725_PERS_20_CYCLE    (0b0111)  /* 20 clean channel values outside threshold range generates an interrupt */
// #define TCS34725_PERS_25_CYCLE    (0b1000)  /* 25 clean channel values outside threshold range generates an interrupt */
// #define TCS34725_PERS_30_CYCLE    (0b1001)  /* 30 clean channel values outside threshold range generates an interrupt */
// #define TCS34725_PERS_35_CYCLE    (0b1010)  /* 35 clean channel values outside threshold range generates an interrupt */
// #define TCS34725_PERS_40_CYCLE    (0b1011)  /* 40 clean channel values outside threshold range generates an interrupt */
// #define TCS34725_PERS_45_CYCLE    (0b1100)  /* 45 clean channel values outside threshold range generates an interrupt */
// #define TCS34725_PERS_50_CYCLE    (0b1101)  /* 50 clean channel values outside threshold range generates an interrupt */
// #define TCS34725_PERS_55_CYCLE    (0b1110)  /* 55 clean channel values outside threshold range generates an interrupt */
// #define TCS34725_PERS_60_CYCLE    (0b1111)  /* 60 clean channel values outside threshold range generates an interrupt */
// #define TCS34725_CONFIG           (0x0D)
// #define TCS34725_CONFIG_WLONG     (0x02)    /* Choose between short and long (12x) wait times via TCS34725_WTIME */
#define TCS34725_CONTROL          (0x0F)    /* Set the gain level for the sensor */
#define TCS34725_ID               (0x12)    /* 0x44 = TCS34721/TCS34725, 0x4D = TCS34723/TCS34727 */
// #define TCS34725_STATUS           (0x13)
// #define TCS34725_STATUS_AINT      (0x10)    /* RGBC Clean channel interrupt */
// #define TCS34725_STATUS_AVALID    (0x01)    /* Indicates that the RGBC channels have completed an integration cycle */
#define TCS34725_CDATAL           (0x14)    /* Clear channel data */
// #define TCS34725_CDATAH           (0x15)
#define TCS34725_RDATAL           (0x16)    /* Red channel data */
// #define TCS34725_RDATAH           (0x17)
#define TCS34725_GDATAL           (0x18)    /* Green channel data */
// #define TCS34725_GDATAH           (0x19)
#define TCS34725_BDATAL           (0x1A)    /* Blue channel data */
// #define TCS34725_BDATAH           (0x1B)

// ----------------------------------- Classe SensorDeCor ----------------------------------- //

SensorDeCor::SensorDeCor() {}

SensorDeCor::SensorDeCor(uint8_t porta) 
{
	switch (porta) {
		case D:
			_sdaPin = PINO_SDA_SENSOR_DE_COR_DIREITO;
			_sclPin = PINO_SCL_SENSOR_DE_COR_DIREITO;
			break;
		case E:
			_sdaPin = PINO_SDA_SENSOR_DE_COR_ESQUERDO;
			_sclPin = PINO_SCL_SENSOR_DE_COR_ESQUERDO;
			break;
		default:
			return;
	}

  _tcs34725Initialised = false;
  _tcs34725IntegrationTime = TCS34725_INTEGRATIONTIME_308MS;
  _tcs34725Gain = TCS34725_GAIN_1X;
  
  _i2c = SoftwareWire (_sdaPin, _sclPin);
}

boolean SensorDeCor::iniciar(void) 
{
  _i2c.begin();
  
  /* Certifica-se que estamos realmente conectados */
  uint8_t x = read8(TCS34725_ID);
  
  if (x != 0x44)
  {
    return false;
  }
  _tcs34725Initialised = true;

  /* Configura o tempo de integração e o ganho */
  setIntegrationTime(_tcs34725IntegrationTime);
  setGain(_tcs34725Gain);

  /* Habilita o dispositivo */
  enable();

  return true;
}

void SensorDeCor::write8 (uint8_t reg, uint32_t value)
{
  _i2c.beginTransmission(TCS34725_ADDRESS);
  _i2c.write(TCS34725_COMMAND_BIT | reg);
  _i2c.write(value & 0xFF); 
  _i2c.endTransmission();
}

uint8_t SensorDeCor::read8(uint8_t reg)
{
  _i2c.beginTransmission(TCS34725_ADDRESS);
  _i2c.write(TCS34725_COMMAND_BIT | reg);
  _i2c.endTransmission();
  _i2c.requestFrom(TCS34725_ADDRESS, 1);
 
  return _i2c.read();
}

uint16_t SensorDeCor::read16(uint8_t reg)
{
  uint16_t x; uint16_t t;

  _i2c.beginTransmission(TCS34725_ADDRESS); 
  _i2c.write(TCS34725_COMMAND_BIT | reg);  
  _i2c.endTransmission();

  _i2c.requestFrom(TCS34725_ADDRESS, 2);

  t = _i2c.read();
  x = _i2c.read();

  x <<= 8;
  x |= t;
  return x;
}

void SensorDeCor::setIntegrationTime(tcs34725IntegrationTime_t it)
{
  if (!_tcs34725Initialised) iniciar();

  /* Atualiza o registrador de tempo */
  write8(TCS34725_ATIME, it);

  /* Atualiza o valor do tempo de integração */
  _tcs34725IntegrationTime = it;
}

void SensorDeCor::setGain(tcs34725Gain_t gain)
{
  if (!_tcs34725Initialised) iniciar();

  /* Atualiza o registrador de tempo */
  write8(TCS34725_CONTROL, gain);

  /* Atualiza o valor do ganho */
  _tcs34725Gain = gain;
}

void SensorDeCor::enable(void)
{
  write8(TCS34725_ENABLE, TCS34725_ENABLE_PON);
  delay(3);
  write8(TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);  
}

void SensorDeCor::obterValores (uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c)
{
  if (!_tcs34725Initialised) iniciar();

  *c = read16(TCS34725_CDATAL);
  *r = read16(TCS34725_RDATAL);
  *g = read16(TCS34725_GDATAL);
  *b = read16(TCS34725_BDATAL);
  
  /* Configura o delay para o tempo de espera */
  switch (_tcs34725IntegrationTime) 
  {
    case TCS34725_INTEGRATIONTIME_2_4MS:
      delay(3);
      break;
    case TCS34725_INTEGRATIONTIME_24MS:
      delay(24);
      break;
    case TCS34725_INTEGRATIONTIME_50MS:
      delay(50);
      break;
    case TCS34725_INTEGRATIONTIME_101MS:
      delay(101);
      break;
    case TCS34725_INTEGRATIONTIME_154MS:
      delay(154);
      break;
    case TCS34725_INTEGRATIONTIME_308MS:
      delay(308);
      break;
    case TCS34725_INTEGRATIONTIME_700MS:
      delay(700);
      break;
  }
}
