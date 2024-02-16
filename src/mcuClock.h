

#ifndef MCUCLOCK_H_
#define MCUCLOCK_H_

#include "time.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void            set_system_time(time_t timestamp);

void            system_tick(void);
/**
time_t _mkTime(Time time,volatile time_t *systemTime);
Time _getTime(time_t timeValue);**/

#endif /* MCUCLOCK_H_ */