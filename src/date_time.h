

#ifndef DATE_TIME_H_
#define DATE_TIME_H_

#include "sTime.h"

time_t _mkTime(Time time,volatile time_t *systemTime);
Time _getTime(time_t timeValue);

#endif /* DATE_TIME_H_ */