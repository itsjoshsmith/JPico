#ifndef JSERIAL_H
#define JSERIAL_H

#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "JUtils/JTimer.h"

typedef struct
{
  uart_inst_t *uart;
  uint baud_rate;
  uint tx_pin;
  uint rx_pin;
} JSerial;


void jserial_init(JSerial *serial, uart_inst_t *uart, uint baud_rate, uint tx_pin, uint rx_pin);
void jserial_write_char(JSerial *serial, char c);
void jserial_write_string(JSerial *serial, const char *str);
bool jserial_available(JSerial *serial);
char jserial_get_char(JSerial *serial);
bool jserial_read_until_char(JSerial *serial, char terminator, char *buffer, size_t bufferSize, unsigned int timeout_ms);
bool jserial_read_bytes(JSerial *serial, char *buffer, size_t numBytes, unsigned int timeout_ms);

#endif // JSERIAL_H