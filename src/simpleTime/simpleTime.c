#include <stdio.h>
#include "simpleTime.h"
#include <stdint.h>

uint16_t calcYear(uint32_t *days);
uint8_t daysInMonth(uint16_t year, uint8_t month);
uint8_t calcUTCOffset(uint32_t epochTimeY2K);
uint8_t calcMonth(uint32_t *days, uint16_t year);

clock_t s_clock(void) {
    return (clock_t)-1;
}

//time1 - time0
int32_t s_difftime(uint32_t time1, uint32_t time0) {
    int64_t diff = (int64_t)time1 - (int64_t)time0;


    if (diff > INT32_MAX || diff < INT32_MIN) {
        return INT32_MIN;
    }
    return (int32_t)diff;
}

// Converts the given year, month, day, hour, minute, and second into seconds since the epoch
uint32_t s_mktime(struct tm * timeptr) {
    const struct tm time = (*timeptr);
    // Calculate number of days since the epoch
    uint16_t days_since_epoch = (time.tm_year - EPOCH_YEAR) * 365;
    for (uint16_t y = EPOCH_YEAR; y < time.tm_year; y++) {
        if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
            days_since_epoch++; // Leap year
    }
    for (uint8_t m = 1; m < time.tm_mon; m++)
        days_since_epoch += daysInMonth(time.tm_year, m);

    // Calculate seconds since the epoch
    uint32_t seconds_since_epoch = days_since_epoch * ONE_DAY;
    seconds_since_epoch += (time.tm_mday - 1) * ONE_DAY;
    seconds_since_epoch += time.tm_hour * ONE_HOUR;
    seconds_since_epoch += time.tm_min * 60;
    seconds_since_epoch += time.tm_sec;

    return seconds_since_epoch;
}

uint32_t s_time(const uint32_t *timer){
    return (*timer);
}
char *s_ctime(const uint32_t *timer) {
    return s_asctime(s_localtime((const uint32_t *) timer));
}

char *s_asctime(const struct tm * timeptr){
    static char result[30];

    // Construct the string in the format: "YYYY-MM-DD HH:MM:SS"
    sprintf(result, "%04d-%02d-%02d %02d:%02d:%02d",
            timeptr->tm_year, timeptr->tm_mon, timeptr->tm_mday,
            timeptr->tm_hour, timeptr->tm_min, timeptr->tm_sec);
    return result;
}

struct tm *s_gmtime(const uint32_t * timer) {
    uint32_t timeValue = (*timer);

    uint8_t seconds = timeValue % 60;
    timeValue /= 60;
    uint8_t minutes = timeValue % 60;
    timeValue /= 60;
    uint8_t hours = timeValue % 24;
    timeValue /= 24;
    uint32_t days = timeValue;
    // Convert days since epoch to year, month, day
    uint16_t year = calcYear(&days);
    // Find the month and day
    uint8_t month = calcMonth(&days, year);
    uint8_t day = days + 1; // Days start from 0, so add 1

    // Allocate memory for a struct tm structure
    struct tm *constructedTime = (struct tm *)malloc(sizeof(struct tm));
    if (constructedTime == NULL) {
        return NULL;
    }

    constructedTime->tm_sec = seconds;
    constructedTime->tm_min = minutes;
    constructedTime->tm_hour = hours;
    constructedTime->tm_mday = day;
    constructedTime->tm_mon = month;
    constructedTime->tm_year = year;

    return constructedTime;
}

struct tm *s_localtime(const uint32_t * timer) {
    uint32_t timeValue = (*timer);
    uint8_t UTC_offset = calcUTCOffset((*timer));

    // Convert epoch time to local time in Berlin
    timeValue += UTC_offset * 3600; // Adjust for UTC offset
    return s_gmtime((const uint32_t *) &timeValue);
}

size_t s_strftime(char *s, size_t maxsize, const char *format, const struct tm *timeptr) {
    return 0; // Always return 0 as per your requirement
}

//time1 - time0
uint32_t s_difftime_unsigned(uint32_t time1, uint32_t time0) {

    int64_t diff = (int64_t)time1 - (int64_t)time0;

    return (uint32_t)(diff >= 0 ? diff : -diff);
}

// Returns the number of days in a given month of a given year
uint8_t daysInMonth(uint16_t year, uint8_t month) {
    static const uint8_t days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    uint8_t days_in_month = days[month - 1];
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
        days_in_month++; // Leap year
    return days_in_month;
}

uint8_t isDST(uint8_t month, uint8_t day) {
    // DST in Germany starts on the last Sunday of March and ends on the last Sunday of October

    // Check if month is March through October
    if (month < 3 || month > 10)
        return 0;

    // Calculate the day of the week for the last day of the month
    uint8_t lastDayOfWeek = (5 + (31 * (month - 1) - 7) % 7) % 7; // Zeller's Congruence

    // Determine the date of the last Sunday of the month
    uint8_t lastSunday = 31 - lastDayOfWeek;

    // Check if the day is within the last week of the month
    if (day > lastSunday)
        return 1; // Last week of the month, DST in effect

    return 0;
}

// Function to get the UTC offset based on whether daylight saving time (DST) is in effect
uint8_t getUTCOffset(uint8_t month, uint8_t day) {
    return isDST(month, day) ? 2 : 1; // DST in effect, UTC+2 (CEST)  Standard time, UTC+1 (CET)
}

uint16_t calcYear(uint32_t *days)
{
    uint16_t year = EPOCH_YEAR;
    while ((*days) >= 365 + ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {

            (*days) -= 366;
            year++;
        }	 else {
            (*days) -= 365;
            year++;
        }
    }
    return year;
}

uint8_t calcMonth(uint32_t *days, uint16_t year)
{
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
    uint8_t day = days + 1; // Days start from 0, so add 1

    // Get the UTC offset based on whether daylight saving time (DST) is in effect
    return getUTCOffset(month, day);
}