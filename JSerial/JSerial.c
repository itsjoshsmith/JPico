/*
 * Copyright (c) 2025 Josh Smith
 * Licensed under the MIT license.
 */

#include "JSerial.h"

// Initialize the Serial wrapper
void jserial_init(JSerial *serial, uart_inst_t *uart, uint baud_rate, uint tx_pin, uint rx_pin)
{
  serial->uart = uart;
  serial->baud_rate = baud_rate;
  serial->tx_pin = tx_pin;
  serial->rx_pin = rx_pin;

  // Initialize UART
  uart_init(serial->uart, serial->baud_rate);

  // Set the TX and RX pins
  gpio_set_function(serial->tx_pin, GPIO_FUNC_UART);
  gpio_set_function(serial->rx_pin, GPIO_FUNC_UART);
}

// Send a single character
void jserial_write_char(JSerial *serial, char c)
{
  uart_putc(serial->uart, c);
}

// Send a string
void jserial_write_string(JSerial *serial, const char *str)
{
  while (*str)
    jserial_write_char(serial, *str++);

}

// Check if data is available to read
bool jserial_available(JSerial *serial)
{
  return uart_is_readable(serial->uart);
}

// Read a single character (blocking)
char jserial_get_char(JSerial *serial)
{
  return uart_getc(serial->uart);
}

// Read until a terminating character and fill the provided buffer
bool jserial_read_until_char(JSerial *serial, char terminator, char *buffer, size_t bufferSize, unsigned int timeout_ms)
{
  size_t length = 0;
  
  JTimer timer;
  jtimer_init(&timer, timeout_ms);
  jtimer_start(&timer);

  while (true)
  {
    if (jtimer_has_expired(&timer))
      return false;
    
    if (jserial_available(serial))
    {
      char c = jserial_get_char(serial);

      if (length + 1 >= bufferSize)
        return false;
      
      buffer[length++] = c;

      if (c == terminator)
        break;

    }
  }

  buffer[length] = '\0';
  return true;
}

// Read a specified number of bytes into the provided buffer
bool jserial_read_bytes(JSerial *serial, char *buffer, size_t numBytes, unsigned int timeout_ms)
{
  size_t bytesRead = 0;
  JTimer timer;

  jtimer_init(&timer, timeout_ms);
  jtimer_start(&timer);

  while (bytesRead < numBytes)
  {
    if (jtimer_has_expired(&timer))
      return false;
    
    if (jserial_available(serial))
      buffer[bytesRead++] = jserial_get_char(serial);
    
  }

  return true;
}