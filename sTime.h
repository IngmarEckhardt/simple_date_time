#ifndef STIME_H_
#define STIME_H_


#include <avr/io.h>

typedef uint32_t time_t;

typedef struct {
	uint16_t year; 
	uint8_t month; 
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	} Time;

#include "date_time.h"

time_t mkTime(Time time);
Time getTime();

void tickSecond();



#endif /* STIME_H_ */