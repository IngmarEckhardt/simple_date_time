#include "mcuClock.h"

volatile uint32_t systemTime;

uint32_t getSystemTime() {
    uint32_t ret;
    uint8_t sreg;

    // Disable interrupts and save the previous state
    sreg = SREG;
    cli();

    // Read the value of systemTime
    ret = systemTime;

    // Restore the previous state (enable interrupts if they were enabled before)
    SREG = sreg;

    // Return the value
    return ret;
}

void setSystemTime(uint32_t timestamp) {
    uint8_t sreg;
    // Disable interrupts and save the previous state
    sreg = SREG;
    cli();

    systemTime = timestamp;

    // Restore the previous state (enable interrupts if they were enabled before)
    SREG = sreg;
}

void tickSecond(){
    uint8_t sreg;
    sreg = SREG;
    cli();
    systemTime++;
    SREG = sreg;
}