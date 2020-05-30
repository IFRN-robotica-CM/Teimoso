
#ifndef _SensorDeCor_h
#define _SensorDeCor_h

#include <Arduino.h>
#include <Wire.h>
#include "SoftwareWire/SoftwareWire.h"

typedef enum
{
  TCS34725_INTEGRATIONTIME_2_4MS  = 0xFF,   /**<  2.4ms - 1 cycle    - Max Count: 1024  */
  TCS34725_INTEGRATIONTIME_24MS   = 0xF6,   /**<  24ms  - 10 cycles  - Max Count: 10240 */
  TCS34725_INTEGRATIONTIME_50MS   = 0xEB,   /**<  50ms  - 20 cycles  - Max Count: 20480 */
  TCS34725_INTEGRATIONTIME_101MS  = 0xD5,   /**<  101ms - 42 cycles  - Max Count: 43008 */
  TCS34725_INTEGRATIONTIME_154MS  = 0xC0,   /**<  154ms - 64 cycles  - Max Count: 65535 */
  TCS34725_INTEGRATIONTIME_308MS  = 0xB2,   /**<  308ms - 128 cycles - Max Count: 65535 */
  TCS34725_INTEGRATIONTIME_700MS  = 0x00    /**<  700ms - 256 cycles - Max Count: 65535 */
}
tcs34725IntegrationTime_t;

typedef enum
{
  TCS34725_GAIN_1X                = 0x00,   /**<  No gain  */
  TCS34725_GAIN_4X                = 0x01,   /**<  2x gain  */
  TCS34725_GAIN_16X               = 0x02,   /**<  16x gain */
  TCS34725_GAIN_60X               = 0x03    /**<  60x gain */
}
tcs34725Gain_t;

// ----------------------------------- Classe SensorDeCor ----------------------------------- //

class SensorDeCor {
  public:
    SensorDeCor();
    SensorDeCor(uint8_t porta); 
    boolean  iniciar(void);
    void     obterValores(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c);

  private:
    boolean _tcs34725Initialised;
    tcs34725Gain_t _tcs34725Gain;
    tcs34725IntegrationTime_t _tcs34725IntegrationTime; 
    uint8_t _sdaPin;
    uint8_t _sclPin;
    SoftwareWire _i2c;

    void     setIntegrationTime(tcs34725IntegrationTime_t it);
    void     setGain(tcs34725Gain_t gain);
    void     write8 (uint8_t reg, uint32_t value);
    uint8_t  read8 (uint8_t reg);
    uint16_t read16 (uint8_t reg);
    void     enable(void);
};

#endif
