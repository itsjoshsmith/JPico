#ifndef JTIMER_H
#define JTIMER_H

#include "pico/stdlib.h"

typedef struct
{
  uint32_t start_time;
  uint32_t stop_time;
  unsigned int timeout;
  bool has_started;
  bool has_stopped;
  bool is_running;
} JTimer;

void jtimer_init(JTimer *timer, unsigned int timeout);
void jtimer_start(JTimer *timer);
void jtimer_stop(JTimer *timer);
void JTimer_reset(JTimer *timer);
uint32_t jtimer_elapsed_complete(JTimer *timer);
bool jtimer_has_expired(JTimer *timer);

#endif // JTIMER_H