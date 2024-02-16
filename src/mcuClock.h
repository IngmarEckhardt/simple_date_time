#ifndef MCUCLOCK_H_
#define MCUCLOCK_H_

#include "time.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void            set_system_time(time_t timestamp);

time_t          getSystemTime(void);

void            tickSecond(void);

#endif /* MCUCLOCK_H_ */