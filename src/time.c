#include <time.h>
#include <simpleTime/simpleTime.h>

clock_t         clock(void) {return s_clock();}

int32_t         difftime(time_t time1, time_t time0) {return s_difftime(time1,time0);}

time_t          mktime(struct tm * timeptr) {return s_mktime(timeptr);}

time_t          time(const time_t *timer){return s_time(timer);}

char            *ctime (const time_t *timer){return s_ctime(timer);}

char            *asctime(const struct tm * timeptr) {return s_asctime(timeptr);}

struct tm       *gmtime(const time_t * timer){return s_gmtime(timer);}

struct tm       *localtime(const time_t * timer){return s_localtime(timer);}

size_t          strftime(char *s, size_t maxsize, const char *format, const struct tm *timeptr){return s_strftime(s, maxsize, format, timeptr);}
