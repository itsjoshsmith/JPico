/*
 * Copyright (c) 2025 Josh Smith
 * Licensed under the MIT license.
 */

#include "JAHT10.h"

// Initialize the JAHT10 sensor
void jaht10_init(JAHT10 *sensor, i2c_inst_t *i2c_instance, uint8_t address)
{
  sensor->instance = i2c_instance;
  sensor->address = address;
  for (int i = 0; i < 6; i++)
  {
    sensor->raw_data_buffer[i] = 0xFF; // Initialize buffer to default values
  }
}

// Begin communication with the sensor
bool jaht10_begin(JAHT10 *sensor)
{
  // Initialize I2C
  i2c_init(sensor->instance, 100000);
  gpio_set_function(4, GPIO_FUNC_I2C);
  gpio_set_function(5, GPIO_FUNC_I2C);
  gpio_pull_up(4);
  gpio_pull_up(5);

  // Perform a soft reset
  if (!jaht10_soft_reset(sensor))
  {
    return false;
  }

  // Send calibration command
  uint8_t cmd[3] = {AHT10_CMD_CALIBRATE, 0x08, 0x00};
  i2c_write_blocking(sensor->instance, sensor->address, cmd, 3, false);

  // Wait for the sensor to be ready
  while (jaht10_get_status(sensor) & AHT10_STATUS_BUSY)
  {
    sleep_ms(10);
  }

  // Check if the sensor is calibrated
  if (!(jaht10_get_status(sensor) & AHT10_STATUS_CALIBRATED))
  {
    return false;
  }

  return true;
}

// Read raw data from the sensor
bool jaht10_read_raw_data(JAHT10 *sensor)
{
  uint8_t cmd[3] = {AHT10_CMD_TRIGGER, 0x33, 0x00};
  if (i2c_write_blocking(sensor->instance, sensor->address, cmd, 3, false) != 3)
  {
    return false;
  }

  sleep_ms(100);

  // Wait for the sensor to be ready
  while (jaht10_get_status(sensor) & AHT10_STATUS_BUSY)
  {
    sleep_ms(10);
  }

  // Read 6 bytes of raw data
  int res = i2c_read_blocking(sensor->instance, sensor->address, sensor->raw_data_buffer, 6, false);
  if (res != 6)
  {
    return false;
  }

  return true;
}

// Read temperature from the sensor
float jaht10_read_temperature(JAHT10 *sensor)
{
  if (!jaht10_read_raw_data(sensor))
  {
    return 0.0f;
  }

  if (sensor->raw_data_buffer[0] == 0xFF)
  {
    return 0.0f;
  }

  uint32_t tdata = sensor->raw_data_buffer[3] & 0x0F;
  tdata <<= 8;
  tdata |= sensor->raw_data_buffer[4];
  tdata <<= 8;
  tdata |= sensor->raw_data_buffer[5];
  return ((float)tdata * 200 / 0x100000) - 50;
}

// Read humidity from the sensor
float jaht10_read_humidity(JAHT10 *sensor)
{
  if (!jaht10_read_raw_data(sensor))
  {
    return 0.0f;
  }

  if (sensor->raw_data_buffer[0] == 0xFF)
  {
    return 0.0f;
  }

  uint32_t h = sensor->raw_data_buffer[1];
  h <<= 8;
  h |= sensor->raw_data_buffer[2];
  h <<= 4;
  h |= sensor->raw_data_buffer[3] >> 4;
  return ((float)h * 100) / 0x100000;
}

// Get the status of the sensor
uint8_t jaht10_get_status(JAHT10 *sensor)
{
  uint8_t rxBuf;
  i2c_read_blocking(sensor->instance, sensor->address, &rxBuf, 1, false);
  return rxBuf;
}

// Perform a soft reset on the sensor
bool jaht10_soft_reset(JAHT10 *sensor)
{
  uint8_t cmd = AHT10_CMD_SOFTRESET;
  if (i2c_write_blocking(sensor->instance, sensor->address, &cmd, 1, false) == 1)
  {
    sleep_ms(20);
    return true;
  }
  return false;
}