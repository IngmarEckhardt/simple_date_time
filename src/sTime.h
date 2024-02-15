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
//set SystemTime with a Time-Object in UTC
time_t mkTime(Time time);
//get a Time-Object made from system time in CET or CEST
Time getTime();
//use this to connect the time to a counter interrupt routine or another clock source.
void tickSecond();



#endif /* STIME_H_ */