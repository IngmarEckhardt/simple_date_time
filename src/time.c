#include <stdio.h>
#include "time.h"
#include <stdint.h>


//helper functions
uint16_t calcYear(uint32_t *days);

uint8_t daysInMonth(uint16_t year, uint8_t month);

uint8_t calcUTCOffset(uint32_t epochTimeY2K);

uint8_t calcMonth(uint32_t *days, uint16_t year);

uint8_t isDST(uint16_t year, uint8_t month, uint8_t day);

uint8_t calcZellerCongruence(uint16_t year, uint8_t month, uint8_t day);

uint8_t isLeapYear(uint16_t year);

//expecting no mcu library use this function, because it is per default unknown in a mcu environment without rtc
//calculate this value with systemClock and CLOCKS_PER_SECOND or F_CPU in mcuClock if necessary and subtract the sleep times
// to keep this implementation as close as possible to the ansi/iso 9899-1990. After implementation connect it to the version in time.h
uint32_t s_clock(void) {
    return -1;
}

//time1 - time0
int32_t difftime(uint32_t time1, uint32_t time0) {

    // 0 - uint32_t_max exceeds max negative values of int32_T, avoid the operation
    int64_t diff = (int64_t) time1 - (int64_t) time0;
    //return INT32_MIN if we exceed its boundary
    return (diff < INT32_MIN) ? INT32_MIN : (int32_t) diff;
}

// Converts the given year, month, day, hour, minute, and second into seconds since the epoch
uint32_t s_mktime(const struct tm *timeptr) {
    const struct tm time = (*timeptr);

    // Calculate number of days since the epoch
    uint16_t days_since_epoch = (time.tm_year - EPOCH_YEAR) * 365;

    // add one day for leap years
    for (uint16_t y = EPOCH_YEAR; y < time.tm_year; y++) {
        if (isLeapYear(y))
            days_since_epoch++;
    }

    for (uint8_t m = 1; m < time.tm_mon; m++) {
        days_since_epoch += daysInMonth(time.tm_year, m);
    }

    uint32_t seconds_since_epoch = days_since_epoch * ONE_DAY;
    seconds_since_epoch += (time.tm_mday - 1) * ONE_DAY;
    seconds_since_epoch += time.tm_hour * ONE_HOUR;
    seconds_since_epoch += time.tm_min * 60;
    seconds_since_epoch += time.tm_sec;

    return seconds_since_epoch;
}

uint8_t isLeapYear(uint16_t year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

uint32_t time(const uint32_t *timer) {
    return (*timer);
}

char *ctime(const uint32_t *timer) {
    return asctime(localtime(timer));
}

char *asctime(const struct tm *timeptr) {
    char *result;

    switch (timeptr->tm_isdst) {
        case 1: {
            result = (char *) malloc(CET_STRING_SIZE * sizeof(char));
            if (result == NULL) {
                return NULL;
            }
            sprintf(result, "%04d-%02d-%02d %02d:%02d:%02d(CET)",
                    timeptr->tm_year, timeptr->tm_mon, timeptr->tm_mday,
                    timeptr->tm_hour, timeptr->tm_min, timeptr->tm_sec);
            break;
        }
        case 2: {
            result = (char *) malloc(CEST_STRING_SIZE * sizeof(char));
            if (result == NULL) {
                return NULL;
            }
            sprintf(result, "%04d-%02d-%02d %02d:%02d:%02d(CEST)",
                    timeptr->tm_year, timeptr->tm_mon, timeptr->tm_mday,
                    timeptr->tm_hour, timeptr->tm_min, timeptr->tm_sec);
            break;
        }
        default: {
            result = (char *) malloc(UTC_STRING_SIZE * sizeof(char));
            if (result == NULL) {
                return NULL;
            }
            sprintf(result, "%04d-%02d-%02d %02d:%02d:%02d",
                    timeptr->tm_year, timeptr->tm_mon, timeptr->tm_mday,
                    timeptr->tm_hour, timeptr->tm_min, timeptr->tm_sec);
            break;
        }
    }
    return result;
}

struct tm *gmtime(const uint32_t *timer) {
    // Allocate memory for a struct time structure
    struct tm *constructedTime = (struct tm *) malloc(sizeof(struct tm));
    if (constructedTime == NULL) {
        return NULL;
    }
    uint32_t timeValue = (*timer);

    constructedTime->tm_sec = timeValue % 60;
    timeValue /= 60;
    constructedTime->tm_min = timeValue % 60;
    timeValue /= 60;
    constructedTime->tm_hour = timeValue % 24;
    timeValue /= 24;
    // Convert days since epoch to year, month, day
    constructedTime->tm_year = calcYear(&timeValue);
    // Find the month and day
    constructedTime->tm_mon = calcMonth(&timeValue, constructedTime->tm_year);
    constructedTime->tm_mday = timeValue + 1; // Days start from 0, so add 1

    return constructedTime;
}

struct tm *localtime(const uint32_t *timer) {
    uint32_t timeValue = (*timer);
    uint8_t UTC_offset = calcUTCOffset((*timer));
    // Adjust for UTC offset
    timeValue += UTC_offset * ONE_HOUR;
    struct tm *timeToReturn = gmtime(&timeValue);

    timeToReturn->tm_isdst = UTC_offset;
    return timeToReturn;
}

size_t strftime(char *s, size_t maxsize, const char *format, const struct tm *timeptr) {
    return 0; // Always return 0 as per your requirement
}

//time1 - time0
uint32_t difftime_unsigned(uint32_t time1, uint32_t time0) {

    int64_t diff = (int64_t) time1 - (int64_t) time0;
    return (uint32_t) (diff >= 0 ? diff : -diff);
}

// Returns the number of days in a given month of a given year
uint8_t daysInMonth(uint16_t year, uint8_t month) {

    static const uint8_t days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    uint8_t days_in_month = days[month - 1];

    if (month == 2 && isLeapYear(year)) { days_in_month++; }

    return days_in_month;
}

uint8_t calcZellerCongruence(uint16_t year, uint8_t month, uint8_t day) {
    uint32_t h;
    if (month == 1) {
        month = 13;
        year--;
    }
    if (month == 2) {
        month = 14;
        year--;
    }
    h = day + 13 * (month + 1) / 5 + (year % 100) + (year % 100) / 4 + (year / 100) / 4 + 5 * (year / 100);
    h = h % 7;
    return h;
}

uint8_t isDST(uint16_t year, uint8_t month, uint8_t day) {
    // DST in Germany starts on the last Sunday of March and ends on the last Sunday of October

    if (month > 3 && month < 10) {
        return 1;
    }

    // Check if month is March through October
    if (month < 3 || month > 10) {
        return 0;
    }

    // Calculate the day of the week for the last day of the month
    uint8_t lastDayOfMonth = calcZellerCongruence(year, month, 31);

    // Determine the date of the last Sunday of the month
    uint8_t lastSunday = 31 - ((lastDayOfMonth - 1) % 7);

    if ((day >= lastSunday && month == 3) || (day < lastSunday && month == 10)) {
        return 1;
    }
    return 0;
}

uint16_t calcYear(uint32_t *days) {
    uint16_t year = EPOCH_YEAR;
    while ((*days) >= 365 + isLeapYear(year)) {
        if (isLeapYear(year)) {
            (*days) -= 366;
            year++;
        } else {
            (*days) -= 365;
            year++;
        }
    }
    return year;
}

uint8_t calcMonth(uint32_t *days, uint16_t year) {
    uint8_t month = 1;
    while ((*days) >= daysInMonth(year, month)) {
        (*days) -= daysInMonth(year, month);
        month++;
    }
    return month;
}

uint8_t calcUTCOffset(uint32_t epochTimeY2K) {
    uint32_t days = epochTimeY2K /= ONE_DAY;
    // Convert days since epoch to year, month, day
    uint16_t year = calcYear(&days);
    // Find the month and day
    uint8_t month = calcMonth(&days, year);
    // Days start from 0, so add 1
    uint8_t day = days + 1;
    // Get the UTC offset based on whether daylight saving time (DST) is in effect
    return isDST(year, month, day) ? 2 : 1;
}