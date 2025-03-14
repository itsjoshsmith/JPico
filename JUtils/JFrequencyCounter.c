/*
 * Copyright (c) 2025 Josh Smith
 * Licensed under the MIT license.
 */

#include "JFrequencyCounter.h"

// Initialize the frequency counter
void jfrequencycounter_init(JFrequencyCounter *counter)
{
  counter->start_time = 0;
  counter->count = 0;
  counter->reset_limit = 0;
}

// Start the frequency counter without a reset limit
void jfrequencycounter_start(JFrequencyCounter *counter)
{
  counter->reset_limit = 0;
  counter->count = 0;
  counter->start_time = to_ms_since_boot(get_absolute_time());
}

// Start the frequency counter with a reset limit
void jfrequencycounter_start_with_limit(JFrequencyCounter *counter, uint64_t reset_limit)
{
  counter->reset_limit = reset_limit;
  counter->count = 0;
  counter->start_time = to_ms_since_boot(get_absolute_time());
}

// Reset the frequency counter
void jfrequencycounter_reset(JFrequencyCounter *counter)
{
  counter->count = 0;
  counter->start_time = to_ms_since_boot(get_absolute_time());
}

// Trigger the frequency counter (increment the count)
void jfrequencycounter_trigger(JFrequencyCounter *counter)
{
  counter->count++;

  // Reset if the reset limit is exceeded
  if (counter->reset_limit > 0 && counter->count > counter->reset_limit)
  {
    jfrequencycounter_reset(counter);
  }
}

// Get the frequency in Hz
double jfrequencycounter_get_frequency_hz(JFrequencyCounter *counter)
{
  uint64_t elapsed_time = to_ms_since_boot(get_absolute_time()) - counter->start_time;
  double elapsed_seconds = elapsed_time / 1000.0; // Convert milliseconds to seconds
  if (elapsed_seconds == 0)
  {
    return 0;
  }
  return counter->count / elapsed_seconds; // Calculate frequency
}