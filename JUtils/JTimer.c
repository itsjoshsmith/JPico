#include "JTimer.h"

// Initialize the timer with a timeout value
void jtimer_init(JTimer *timer, unsigned int timeout)
{
  timer->timeout = timeout;
  timer->has_started = false;
  timer->has_stopped = false;
  timer->is_running = false;
  timer->start_time = 0;
  timer->stop_time = 0;
}

// Start the timer
void jtimer_start(JTimer *timer)
{
  timer->start_time = to_ms_since_boot(get_absolute_time());
  timer->has_started = true;
  timer->has_stopped = false;
  timer->is_running = true;
}

// Stop the timer
void jtimer_stop(JTimer *timer)
{
  timer->stop_time = to_ms_since_boot(get_absolute_time());
  timer->has_started = true;
  timer->has_stopped = true;
  timer->is_running = false;
}

// Reset the timer
void jtimer_reset(JTimer *timer)
{
  timer->has_started = false;
  timer->has_stopped = false;
  timer->is_running = false;
  timer->start_time = 0;
  timer->stop_time = 0;
}

// Get the elapsed time if the timer has completed
uint32_t jtimer_elapsed_complete(JTimer *timer)
{
  if (!timer->is_running && timer->has_started && timer->has_stopped)
  {
    return timer->stop_time - timer->start_time;
  }
  return 0;
}

// Check if the timer has expired
bool jtimer_has_expired(JTimer *timer)
{
  return to_ms_since_boot(get_absolute_time()) - timer->start_time > timer->timeout;
}