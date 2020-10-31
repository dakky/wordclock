#ifdef UNIT_TEST

#include <unity.h>
#include <cstdint>
#include "internal/internalTimefunctions.h"

void test_isSleeptime() 
{
    uint8_t hours = 14;
    uint8_t minutes = 0;
    uint8_t startHour = 22;
    uint8_t startMinute = 0;
    uint8_t endHour = 6;
    uint8_t endMinute = 0;

    TEST_ASSERT_FALSE(InternalTimefunctions.isInSleeptime(hours, minutes, startHour, startMinute, endHour, endMinute ));
}


int main( int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_isSleeptime);

    UNITY_END();
}

#endif