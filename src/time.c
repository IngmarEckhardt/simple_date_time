#include "time.h"

clock_t clock(void) {
    return (clock_t)-1;
}

//time1 - time0.
//int32_t         difftime(time_t time1, time_t time0);


// Returns the number of days in a given month of a given year
uint16_t daysInMonth(uint16_t year, uint8_t month) {
    static const uint8_t days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    uint16_t days_in_month = days[month - 1];
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
        days_in_month++; // Leap year
    return days_in_month;
}

// Converts the given year, month, day, hour, minute, and second into seconds since the epoch
time_t mkTime(struct tm * timeptr) {
    const Time time = (*timeptr);
    // Calculate number of days since the epoch
    uint16_t days_since_epoch = (time.tm_year - EPOCH_YEAR) * 365;
    for (uint16_t y = EPOCH_YEAR; y < time.tm_year; y++) {
        if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
            days_since_epoch++; // Leap year
    }
    for (uint8_t m = 1; m < time.tm_mon; m++)
        days_since_epoch += daysInMonth(time.tm_year, m);

    // Calculate seconds since the epoch
    time_t seconds_since_epoch = days_since_epoch * ONE_DAY;
    seconds_since_epoch += (time.tm_mday - 1) * ONE_DAY;
    seconds_since_epoch += time.tm_hour * ONE_HOUR;
    seconds_since_epoch += time.tm_min * 60;
    seconds_since_epoch += time.tm_sec;

    return seconds_since_epoch;
}

time_t          time(time_t *timer){ return 0; }

char           *asctime(const struct tm * timeptr){ return 0; }

struct tm      *gmtime(const time_t * timer){ return 0; }

struct tm      *localtime(const time_t * timer){ return 0; }



