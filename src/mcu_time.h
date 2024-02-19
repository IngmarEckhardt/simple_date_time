#ifndef MCU_TIME_H
#define MCU_TIME_H
#include <time.h>
#include <inttypes.h>
#include <stdlib.h>


struct time {
    uint8_t  tm_sec;    /**< Seconds [0,59] */
    uint8_t  tm_min;    /**< Minutes [0,59] */
    uint8_t  tm_hour;   /**< Hours [0,23] */
    uint8_t  tm_mday;   /**< Day of the month [1,31] */
    uint8_t  tm_mon;    /**< Month [1,12] */
    uint16_t tm_year;   /**< Year */
    uint8_t  tm_wday;   /**< Day of the week [0,6] (Sunday = 0) not used */
    uint16_t tm_yday;   /**< Day of the year [0,365] not used */
    uint8_t  tm_isdst;  /**< Daylight Saving Time flag, used as:
                             - 0 for UTC
                             - 1 for CET (Central European Time)
                             - 2 for CEST (Central European Summer Time) */
};


#define ONE_HOUR 3600
#define ONE_DAY 86400
#define EPOCH_YEAR 2000
#define UTC_STRING_SIZE 20
#define CET_STRING_SIZE 25
#define CEST_STRING_SIZE 26

uint32_t        s_clock(void);
//time1 - time0, returns int32_t_MIN if calculation exceeds boundaries of int32_t
int32_t         s_difftime(uint32_t time1, uint32_t time0);

uint32_t        s_mktime(const struct time * timeptr);

uint32_t        s_time(const uint32_t *timer);

char            *s_ctime (const uint32_t *timer);

char            *s_asctime(const struct time * timeptr);

struct time       *s_gmtime(const uint32_t * timer);

struct time       *s_localtime(const uint32_t * timer);
//this is a stub to fulfill the iso norm, it returns always 0
size_t          s_strftime(char *s, size_t maxsize, const char *format, const struct time *timeptr);

uint32_t        s_difftime_unsigned(uint32_t time1, uint32_t time0);


#endif //MCU_TIME_H