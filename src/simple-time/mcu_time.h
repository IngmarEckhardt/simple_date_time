#ifndef MCU_TIME_H
#define MCU_TIME_H

#include <inttypes.h>
#include <stdlib.h>
#include <time.h>

#define ONE_HOUR 3600
#define ONE_DAY 86400
#define EPOCH_YEAR 2000
#define UTC_STRING_SIZE 20
#define CET_STRING_SIZE 25
#define CEST_STRING_SIZE 26

uint32_t        s_clock(void);
//time1 - time0, returns int32_t_MIN if calculation exceeds boundaries of int32_t
int32_t         s_difftime(uint32_t time1, uint32_t time0);

uint32_t        s_mktime(const struct tm * timeptr);

uint32_t        s_time(const uint32_t *timer);

char            *s_ctime (const uint32_t *timer);

char            *s_asctime(const struct tm * timeptr);

struct tm       *s_gmtime(const uint32_t * timer);

struct tm       *s_localtime(const uint32_t * timer);
//this is a stub to fulfill the iso norm, it returns always 0
size_t          s_strftime(char *s, size_t maxsize, const char *format, const struct tm *timeptr);

uint32_t        s_difftime_unsigned(uint32_t time1, uint32_t time0);
#endif //MCU_TIME_H