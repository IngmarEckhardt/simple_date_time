#ifndef TIME_H
#define TIME_H

#ifdef __cplusplus
extern          "C" {
#endif

#include <inttypes.h>
//#include <stdlib.h>


typedef uint32_t clock_t;
typedef uint32_t time_t;

#define CLOCKS_PER_SEC ((clock_t)-1)

#define ONE_HOUR 3600

#define ONE_DAY 86400

#define EPOCH_YEAR 2000

struct tm {
    int8_t          tm_sec;
    int8_t          tm_min;
    int8_t          tm_hour;
    int8_t          tm_mday;
    int8_t          tm_wday;
    int8_t          tm_mon;
    int16_t         tm_year;
    int16_t         tm_yday;
    int8_t          tm_isdst;
};

typedef struct tm Time;

clock_t clock(void);

//time1 - time0.
int32_t         difftime(time_t time1, time_t time0);

time_t          mktime(struct tm * timeptr);

time_t          time(time_t *timer);

char           *asctime(const struct tm * timeptr);

struct tm      *gmtime(const time_t * timer);

struct tm      *localtime(const time_t * timer);

uint8_t         is_leap_year(int16_t year);

uint8_t         month_length(int16_t year, uint8_t month);

/* @} */
#ifdef __cplusplus
}
#endif

#endif              /* TIME_H  */
