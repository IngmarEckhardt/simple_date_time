#include <unity.h>
#include <simpleTime.h>

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

    // Calculate the expected result (in this case, the number of seconds since the epoch for the given input)
    uint32_t expected_result = 0; // Assuming January 1st of the epoch year corresponds to 0 seconds since the epoch

    // Assert that the result matches the expected result
    TEST_ASSERT_EQUAL_UINT32(expected_result, result);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_mktime);

    return UNITY_END();
}