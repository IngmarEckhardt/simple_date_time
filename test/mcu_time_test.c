#include "mcu_time_test.h"

void setUp(void) {}
void tearDown(void) {
    free(result);
    free(resultString);
}
int main(void) {
    UNITY_BEGIN();

    //iso functions
    RUN_TEST(mktime_epochStartDateUTC_returnZero);
    RUN_TEST(mktime_februaryThirteenthCET_calculateCorrectly);
    RUN_TEST(mktime_julyThirteenthCEST_calculateCorrectly);
    RUN_TEST(localtime_februaryThirteenthCET_returnCorrectWintertimeStruct);
    RUN_TEST(localtime_julyThirteenthCEST_returnCorrectSummertimeStruct);
    RUN_TEST(asctime_UtcCetCestTimestamps_createThreeStringsWithCorrectTimezones);

    //helper functions
    RUN_TEST(calcYear_startEpoch2YK366days_shouldBeEpochYearPlusOne);
    RUN_TEST(daysInMonth_februaryLeapYear_shouldReturn29);
    RUN_TEST(calcUtcOffset_ForFebruaryAndJuly_shouldReturnBothValuesCorrectly);
    RUN_TEST(calcMonth_59daysLeapYear_returnFebruary);
    RUN_TEST(calcMonth_59daysNonLeapYear_returnMarch);
    RUN_TEST(isDST_julyThirtieth2021_returnTrue);
    RUN_TEST(isDST_octoberTwentySeventh2024_returnFalse);
    RUN_TEST(isDST_octoberTwentySixth2024_returnTrue);
    RUN_TEST(isDST_marchThirtyFirst2024_returnTrue);
    RUN_TEST(isDST_marchThirtieth2024_returnFalse);
    RUN_TEST(calcZellerCongruence_marchThirtieth2024_returnZeroForSaturday);
    RUN_TEST(calcZellerCongruence_marchThirtyFirst2024_returnOneForSunday);
    RUN_TEST(calcZellerCongruence_octoberThirtyFirst2024_return5ForThursday);

    return UNITY_END();
}
//iso functions

void mktime_epochStartDateUTC_returnZero(void) {

    uint32_t resultInt32 = s_mktime(&epochStartDate);
    uint32_t expected_result = 0;
    TEST_ASSERT_EQUAL_UINT32(expected_result, resultInt32);
}
void mktime_februaryThirteenthCET_calculateCorrectly(void) {

    uint32_t resultInt32 = s_mktime(&februaryThirteenth2021);
    uint32_t expected_result = februaryThirteenth2021Time_T;

    TEST_ASSERT_EQUAL_UINT32(expected_result, resultInt32);
}
void mktime_julyThirteenthCEST_calculateCorrectly(void) {

    uint32_t resultInt32 = s_mktime(&julyThirteenth2021);
    uint32_t expected_result = julyThirtieth2021Time_T;

    TEST_ASSERT_EQUAL_UINT32(expected_result, resultInt32);
}

void asctime_UtcCetCestTimestamps_createThreeStringsWithCorrectTimezones(void) {
    // Testing with epochStartDate
    test_asctime_with_timestamp(&epochStartDate, "%04d-%02d-%02d %02d:%02d:%02d", UTC_STRING_SIZE-1);

    // Testing with februaryThirteenth2021
    test_asctime_with_timestamp(&februaryThirteenth2021, "%04d-%02d-%02d %02d:%02d:%02d(CET)", CET_STRING_SIZE-1);

    // Testing with julyThirteenth2021
    test_asctime_with_timestamp(&julyThirteenth2021, "%04d-%02d-%02d %02d:%02d:%02d(CEST)", CEST_STRING_SIZE-1);
}

void localtime_februaryThirteenthCET_returnCorrectWintertimeStruct(void) {

    result = localtime(&februaryThirteenth2021Time_T);
    //add one hour because of CET
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(0, result->tm_sec);
    TEST_ASSERT_EQUAL_INT(0, result->tm_min);
    TEST_ASSERT_EQUAL_INT(1, result->tm_hour);
    TEST_ASSERT_EQUAL_INT(13, result->tm_mday);
    TEST_ASSERT_EQUAL_INT(2, result->tm_mon);
    TEST_ASSERT_EQUAL_INT(2021, result->tm_year);
}
void localtime_julyThirteenthCEST_returnCorrectSummertimeStruct(void) {

    result = localtime(&julyThirtieth2021Time_T);
    //add two hours because of CEST
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(0, result->tm_sec);
    TEST_ASSERT_EQUAL_INT(0, result->tm_min);
    TEST_ASSERT_EQUAL_INT(2, result->tm_hour);
    TEST_ASSERT_EQUAL_INT(13, result->tm_mday);
    TEST_ASSERT_EQUAL_INT(7, result->tm_mon);
    TEST_ASSERT_EQUAL_INT(2021, result->tm_year);
}

//helper functions

void calcYear_startEpoch2YK366days_shouldBeEpochYearPlusOne(void) {
    uint32_t days = 366; // Year 2000 was a Leap Year
    uint16_t resultYear = calcYear(&days);
    TEST_ASSERT_EQUAL_UINT16(EPOCH_YEAR + 1, resultYear);
}

void daysInMonth_februaryLeapYear_shouldReturn29(void) {
    uint8_t resultMonth = daysInMonth(2024, 2);
    TEST_ASSERT_EQUAL_UINT8(29, resultMonth); // Leap year
}

void calcUtcOffset_ForFebruaryAndJuly_shouldReturnBothValuesCorrectly(void) {
    uint8_t resultOffset = calcUTCOffset(februaryThirteenth2021Time_T);
    TEST_ASSERT_EQUAL_UINT8(1, resultOffset);

    uint8_t resultOffset2 = calcUTCOffset(julyThirtieth2021Time_T);
    TEST_ASSERT_EQUAL_UINT8(2, resultOffset2);
}

void isDST_julyThirtieth2021_returnTrue(void) {
    uint8_t resultOffset2 = isDST(2021, 7,13);
    TEST_ASSERT_EQUAL_UINT8(1, resultOffset2);
}

void isDST_octoberTwentySeventh2024_returnFalse(void) {
    uint8_t resultOffset2 = isDST(2024, 10,27);
    TEST_ASSERT_EQUAL_UINT8(0, resultOffset2);
}

void isDST_octoberTwentySixth2024_returnTrue(void) {
    uint8_t resultOffset2 = isDST(2024, 10,26);
    TEST_ASSERT_EQUAL_UINT8(1, resultOffset2);
}
void isDST_marchThirtyFirst2024_returnTrue(void) {
    uint8_t resultOffset2 = isDST(2024, 3,31);
    TEST_ASSERT_EQUAL_UINT8(1, resultOffset2);
}
void isDST_marchThirtieth2024_returnFalse(void) {
    uint8_t resultOffset2 = isDST(2024, 3,30);
    TEST_ASSERT_EQUAL_UINT8(0, resultOffset2);
}
void calcZellerCongruence_marchThirtieth2024_returnZeroForSaturday(void) {
    uint8_t resultOffset2 = calcZellerCongruence(2024, 3,30);
    TEST_ASSERT_EQUAL_UINT8(0, resultOffset2);
}
void calcZellerCongruence_marchThirtyFirst2024_returnOneForSunday(void) {
    uint8_t resultOffset2 = calcZellerCongruence(2024, 3,31);
    TEST_ASSERT_EQUAL_UINT8(1, resultOffset2);
}

void calcZellerCongruence_octoberThirtyFirst2024_return5ForThursday(void) {
    uint8_t resultOffset2 = calcZellerCongruence(2024, 10,31);
    TEST_ASSERT_EQUAL_UINT8(5, resultOffset2);
}

void calcMonth_59daysLeapYear_returnFebruary(void) {
    uint32_t days = 59;
    uint8_t resultMonth = calcMonth(&days, 2024);
    TEST_ASSERT_EQUAL_UINT8(2, resultMonth);
}

void calcMonth_59daysNonLeapYear_returnMarch(void) {
    uint32_t days = 59;
    uint8_t resultMonth = calcMonth(&days, 2023);
    TEST_ASSERT_EQUAL_UINT8(3, resultMonth);
}

// Helper function to test asctime with a given timestamp
void test_asctime_with_timestamp(const struct tm *timestamp, const char *expected_format, size_t expected_length) {
    resultString = asctime(timestamp);
    TEST_ASSERT_NOT_NULL(resultString);

    char expected_result[expected_length];
    sprintf(expected_result, expected_format,
            timestamp->tm_year, timestamp->tm_mon, timestamp->tm_mday,
            timestamp->tm_hour, timestamp->tm_min, timestamp->tm_sec);

    TEST_ASSERT_EQUAL_STRING(expected_result, resultString);
    size_t result_length = 0;
    while (resultString[result_length] != '\0') {
        result_length++;
    }
    TEST_ASSERT_EQUAL_UINT32(expected_length, result_length);
}