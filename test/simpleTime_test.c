#include <unity.h>
#include <simpleTime.h>

uint16_t calcYear(uint32_t *days);

uint8_t daysInMonth(uint16_t year, uint8_t month);

uint8_t calcUTCOffset(uint32_t epochTimeY2K);

uint8_t calcMonth(uint32_t *days, uint16_t year);

#include "simpleTime.c"

void setUp(void) {

}

void tearDown(void) {

}

void test_mktime(void) {
    struct tm time_input;
    time_input.tm_sec = 0;
    time_input.tm_min = 0;
    time_input.tm_hour = 0;
    time_input.tm_mday = 1;
    time_input.tm_mon = 1;
    time_input.tm_year = EPOCH_YEAR;

    // Call the function
    uint32_t result = s_mktime(&time_input);

    uint32_t expected_result = 0; // Assuming January 1st of the epoch year corresponds to 0 seconds since the epoch

    TEST_ASSERT_EQUAL_UINT32(expected_result, result);
}

void test_calcYear(void) {
    uint32_t days = 366; // Year 2000 was a Leap Year
    uint16_t result = calcYear(&days);
    TEST_ASSERT_EQUAL_UINT16(EPOCH_YEAR + 1, result);
}

void test_daysInMonth(void) {
    uint8_t result = daysInMonth(2024, 2); // February 2024
    TEST_ASSERT_EQUAL_UINT8(29, result); // Leap year
}

void test_calcUTCOffset(void) {
    uint32_t epochTime = 666489600; // February 13, 2021 (not in DST)
    uint8_t result = calcUTCOffset(epochTime);
    TEST_ASSERT_EQUAL_UINT8(1, result); // Not in DST, UTC+1 (CET)

    epochTime = 1627615200; // July 30, 2021 (in DST)
    result = calcUTCOffset(epochTime);
    TEST_ASSERT_EQUAL_UINT8(2, result); // In DST, UTC+2 (CEST)
}

void test_calcMonth(void) {
    uint32_t days = 59;
    uint8_t result = calcMonth(&days, 2024);
    TEST_ASSERT_EQUAL_UINT8(2, result);
}

void test_calcMonth_non_leap(void) {
    uint32_t days = 59;
    uint8_t result = calcMonth(&days, 2023);
    TEST_ASSERT_EQUAL_UINT8(3, result);
}

void test_mktime_should_calculate_correct_Value(void) {
    struct tm time_input;
    time_input.tm_sec = 0;
    time_input.tm_min = 0;
    time_input.tm_hour = 0;
    time_input.tm_mday = 13;
    time_input.tm_mon = 2;
    time_input.tm_year = 2021;

    // Call the function
    uint32_t result = s_mktime(&time_input);

    uint32_t expected_result = 666489600;

    TEST_ASSERT_EQUAL_UINT32(expected_result, result);
}

void test_s_localtime(void) {
    uint32_t epochTime = 666489600; // February 13, 2021, 00:00:00 (UTC)

    struct tm *result = s_localtime(&epochTime);

    TEST_ASSERT_NOT_NULL(result);
    //one hour later for CET
    TEST_ASSERT_EQUAL_INT(0, result->tm_sec);
    TEST_ASSERT_EQUAL_INT(0, result->tm_min);
    TEST_ASSERT_EQUAL_INT(1, result->tm_hour);
    TEST_ASSERT_EQUAL_INT(13, result->tm_mday);
    TEST_ASSERT_EQUAL_INT(2, result->tm_mon);
    TEST_ASSERT_EQUAL_INT(2021, result->tm_year);

    // Free the memory allocated by s_localtime
    free(result);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_mktime);
    RUN_TEST(test_mktime_should_calculate_correct_Value);
    RUN_TEST(test_calcYear);
    RUN_TEST(test_daysInMonth);
    RUN_TEST(test_calcUTCOffset);
    RUN_TEST(test_calcMonth);
    RUN_TEST(test_calcMonth_non_leap);
    RUN_TEST(test_s_localtime);
    return UNITY_END();
}