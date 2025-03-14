#ifndef JFREQUENCYCOUNTER_H
#define JFREQUENCYCOUNTER_H

#include "pico/stdlib.h"
#include "pico/time.h"

// Struct to represent the frequency counter
typedef struct
{
  uint64_t start_time;
  uint64_t count;
  uint64_t reset_limit;
} JFrequencyCounter;

// Function declarations
void jfrequencycounter_init(JFrequencyCounter *counter);
void jfrequencycounter_start(JFrequencyCounter *counter);
void jfrequencycounter_start_with_limit(JFrequencyCounter *counter, uint64_t reset_limit);
void jfrequencycounter_reset(JFrequencyCounter *counter);
void jfrequencycounter_trigger(JFrequencyCounter *counter);
double jfrequencycounter_get_frequency_hz(JFrequencyCounter *counter);

#endif // JFREQUENCYCOUNTER_H