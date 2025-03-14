#ifndef Ji2c_H
#define Ji2c_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

// Enum to represent the I2C base
typedef enum
{
  I2C_BASE_0,
  I2C_BASE_1
} Ei2cBase;

// Struct to represent the Ji2c instance
typedef struct
{
  i2c_inst_t *instance; // I2C instance (i2c0 or i2c1)
  uint8_t address;      // I2C device address
  uint8_t sda_pin;      // SDA pin
  uint8_t scl_pin;      // SCL pin
  uint baudrate;        // I2C baudrate
} Ji2c;

// Function declarations
void ji2c_init(Ji2c *i2c, uint8_t address);
void ji2c_init_full(Ji2c *i2c, Ei2cBase base, uint8_t sda_pin, uint8_t scl_pin, uint8_t address);
void ji2c_begin(Ji2c *i2c);
void ji2c_begin_with_baudrate(Ji2c *i2c, uint baudrate);
uint16_t ji2c_read_register16(Ji2c *i2c, uint8_t reg);
uint8_t ji2c_read_register8(Ji2c *i2c, uint8_t reg);
void ji2c_write_register16(Ji2c *i2c, uint8_t reg, uint16_t data);

#endif // Ji2c_H