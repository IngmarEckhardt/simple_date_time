#ifndef SIMPLE_TIME_LIBRARY_TEST_MCU_TIME_TEST_H
#define SIMPLE_TIME_LIBRARY_TEST_MCU_TIME_TEST_H
#include <unity.h>
#include <mcu_time.h>

//declaration for the helper functions that aren't present in the header
uint16_t            calcYear(uint32_t *days);
uint8_t             daysInMonth(uint16_t year, uint8_t month);
uint8_t             calcUTCOffset(uint32_t epochTimeY2K);
uint8_t             calcMonth(uint32_t *days, uint16_t year);
uint8_t             isDST(uint16_t year, uint8_t month, uint8_t day);
uint8_t             calcZellerCongruence(uint16_t year, uint8_t month, uint8_t day);
#include "mcu_time.c"

//test helper
void                test_asctime_with_timestamp(const struct tm *timestamp, const char *expected_format, size_t expected_length);

//functions under Test
void                mktime_epochStartDateUTC_returnZero(void);
void                mktime_februaryThirteenthCET_calculateCorrectly(void);
void                mktime_julyThirteenthCEST_calculateCorrectly(void);
void                asctime_UtcCetCestTimestamps_createThreeStringsWithCorrectTimezones(void);
void                localtime_februaryThirteenthCET_returnCorrectWintertimeStruct(void);
void                localtime_julyThirteenthCEST_returnCorrectSummertimeStruct(void);

//helper under Test
void                calcYear_startEpoch2YK366days_shouldBeEpochYearPlusOne(void);
void                calcMonth_59daysLeapYear_returnFebruary(void);
void                calcMonth_59daysNonLeapYear_returnMarch(void);
void                daysInMonth_februaryLeapYear_shouldReturn29(void);
void                calcUtcOffset_ForFebruaryAndJuly_shouldReturnBothValuesCorrectly(void);
void                isDST_julyThirtieth2021_returnTrue(void);
void                isDST_octoberTwentySeventh2024_returnFalse(void);
void                isDST_octoberTwentySixth2024_returnTrue(void);
void                isDST_marchThirtyFirst2024_returnTrue(void);
void                isDST_marchThirtieth2024_returnFalse(void);
void                calcZellerCongruence_marchThirtieth2024_returnZeroForSaturday(void);
void                calcZellerCongruence_marchThirtyFirst2024_returnOneForSunday(void);
void                calcZellerCongruence_octoberThirtyFirst2024_return5ForThursday(void);

//given
const struct tm     epochStartDate = {0, 0, 0, 1, 1, EPOCH_YEAR};
const struct tm     februaryThirteenth2021 = {0, 0, 0, 13, 2, 2021, 0, 0, 1};
const struct tm     julyThirteenth2021 = {0, 0, 0, 13, 7, 2021, 0, 0, 2};
const uint32_t      februaryThirteenth2021Time_T = 666489600;
const uint32_t      julyThirtieth2021Time_T = 679449600;

//reference with purpose to free the allocated memory in the tearDown function
struct tm*           result;
char*                resultString;
#endif //SIMPLE_TIME_LIBRARY_TEST_MCU_TIME_TEST_H