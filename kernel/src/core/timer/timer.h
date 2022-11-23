#pragma once

#include "pit.h"

// Timer abstraction layer
// Takes all of the timers, selects the best one, and uses it for timing

struct Timer
{
    size_t ticks; // The amount of ticks in the current second
    size_t seconds; // The amount of seconds since the timer started running
    size_t fq; // The frequency of the tick function (when it is updated)
};

extern Timer sys_timer; // The global system timer

// Initializes the system timer, and picks the best hardware to use
inline void init_timer()
{
    set_pit_mode(0x36);
    set_pit_freq(1000); // Hardcoded
    sys_timer.ticks = 0;
    sys_timer.seconds = 0;
    sys_timer.fq = 1000; // Hardcoded
}
