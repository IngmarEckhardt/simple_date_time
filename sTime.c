#include <avr/io.h>
#include <avr/interrupt.h>
#include "sTime.h"
#include "date_time.h"

volatile time_t __systemTime;
uint8_t sreg;

time_t _time_t() {
	 time_t ret;
	 
	 // Disable interrupts and save the previous state
	 sreg = SREG;
	 cli();

	 // Read the value of __systemTime
	 ret = __systemTime;

	 // Restore the previous state (enable interrupts if they were enabled before)
	 SREG = sreg;

	 // Return the value
	 return ret;
};


time_t mkTime(Time timeToCreate) {
	return _mkTime(timeToCreate,&__systemTime);
}

Time getTime(){
	return _getTime(_time_t());
}

void tickSecond(){
	 sreg = SREG;
	 cli();
	__systemTime++;
	SREG = sreg;
}


