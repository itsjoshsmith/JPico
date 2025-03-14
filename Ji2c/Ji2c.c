/*
 * Copyright (c) 2025 Josh Smith
 * Licensed under the MIT license.
 */

#include "Ji2c.h"

// Initialize Ji2c with only the address (default to i2c0)
void Ji2c_init(Ji2c *i2c, uint8_t address)
{
  i2c->instance = i2c0;
  i2c->address = address;
  i2c->sda_pin = PICO_DEFAULT_I2C_SDA_PIN;
  i2c->scl_pin = PICO_DEFAULT_I2C_SCL_PIN;
  i2c->baudrate = 100000; // Default baudrate
}

// Initialize Ji2c with full parameters
void Ji2c_init_full(Ji2c *i2c, Ei2cBase base, uint8_t sda_pin, uint8_t scl_pin, uint8_t address)
{
  if (base == I2C_BASE_0)
  {
    i2c->instance = i2c0;
  }
  else
  {
    i2c->instance = i2c1;
  }
  i2c->sda_pin = sda_pin;
  i2c->scl_pin = scl_pin;
  i2c->address = address;
  i2c->baudrate = 100000; // Default baudrate
}

// Begin I2C communication with the default baudrate
void Ji2c_begin(Ji2c *i2c)
{
  i2c_init(i2c->instance, i2c->baudrate);
  gpio_set_function(i2c->scl_pin, GPIO_FUNC_I2C);
  gpio_set_function(i2c->sda_pin, GPIO_FUNC_I2C);
  gpio_pull_up(i2c->scl_pin);
  gpio_pull_up(i2c->sda_pin);
}

// Begin I2C communication with a specified baudrate
void Ji2c_begin_with_baudrate(Ji2c *i2c, uint baudrate)
{
  i2c->baudrate = baudrate;
  i2c_init(i2c->instance, i2c->baudrate);
  gpio_set_function(i2c->scl_pin, GPIO_FUNC_I2C);
  gpio_set_function(i2c->sda_pin, GPIO_FUNC_I2C);
  gpio_pull_up(i2c->scl_pin);
  gpio_pull_up(i2c->sda_pin);
}

// Read a 16-bit register
uint16_t Ji2c_read_register16(Ji2c *i2c, uint8_t reg)
{
  uint8_t data[2];
  i2c_write_blocking(i2c->instance, i2c->address, &reg, 1, true);
  i2c_read_blocking(i2c->instance, i2c->address, data, 2, false);
  return (data[0] << 8) | data[1];
}

// Read an 8-bit register
uint8_t Ji2c_read_register8(Ji2c *i2c, uint8_t reg)
{
  uint8_t data[1];
  i2c_write_blocking(i2c->instance, i2c->address, &reg, 1, true);
  i2c_read_blocking(i2c->instance, i2c->address, data, 1, false);
  return data[0];
}

// Write a 16-bit value to a register
void Ji2c_write_register16(Ji2c *i2c, uint8_t reg, uint16_t data)
{
  uint8_t buf[3];
  buf[0] = reg;
  buf[1] = (uint8_t)(data >> 8); // High byte
  buf[2] = (uint8_t)data;        // Low byte
  i2c_write_blocking(i2c->instance, i2c->address, buf, 3, true);
}