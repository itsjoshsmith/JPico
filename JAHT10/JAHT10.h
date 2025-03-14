#ifndef JAHT10_H
#define JAHT10_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"

// AHT10 I2C Address and Commands
#define AHT10_I2CADDR_DEFAULT 0x38
#define AHT10_I2CADDR_ALTERNATE 0x39
#define AHT10_CMD_CALIBRATE 0xE1
#define AHT10_CMD_TRIGGER 0xAC
#define AHT10_CMD_SOFTRESET 0xBA
#define AHT10_STATUS_BUSY 0x80
#define AHT10_STATUS_CALIBRATED 0x08

// Struct to represent the JAHT10 instance
typedef struct
{
  uint8_t address;            // I2C address of the sensor
  uint8_t raw_data_buffer[6]; // Buffer to store raw data
  i2c_inst_t *instance;       // I2C instance (i2c0 or i2c1)
} JAHT10;

// Function declarations
void jaht10_init(JAHT10 *sensor, i2c_inst_t *i2c_instance, uint8_t address);
bool jaht10_begin(JAHT10 *sensor);
float jaht10_read_temperature(JAHT10 *sensor);
float jaht10_read_humidity(JAHT10 *sensor);
bool jaht10_soft_reset(JAHT10 *sensor);
uint8_t jaht10_get_status(JAHT10 *sensor);
bool jaht10_read_raw_data(JAHT10 *sensor);

#endif // JAHT10_H