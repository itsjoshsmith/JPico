#include <stdio.h>
#include "pico/stdlib.h"
#include "JSerial/JSerial.h"

static char rx_buffer[100];

int main()
{
  stdio_init_all();

  JSerial serial;
  jserial_init(&serial, uart0, 9600, 0, 1);
  
  while (true)
  {
    jserial_write_string(&serial, "1\n");
    jserial_read_until_char(&serial, '\n', rx_buffer, 100, 1000);    
    sleep_ms(1000);
  }
}
