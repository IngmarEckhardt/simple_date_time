#include "mcuClock.h"

volatile time_t systemTime;
uint8_t sreg;

time_t getEpochTime() {
    time_t ret;

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

void tickSecond(){
    sreg = SREG;
    cli();
    systemTime++;
    SREG = sreg;
}






uint8_t isDST(uint16_t year, uint8_t month, uint8_t day) {
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
uint8_t getUTCOffset(uint16_t year, uint8_t month, uint8_t day) {
	return isDST(year, month, day) ? 2 : 1; // DST in effect, UTC+2 (CEST)  Standard time, UTC+1 (CET)
}

uint16_t calcYear(uint32_t *days)
{
	uint16_t year = EPOCH_YEAR;
	while ((*days) >= 365 + ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
		 if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			 
		 (*days) -= 366; 
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

uint8_t calcUTCOffset(time_t epochTimeY2K) {
	
		uint32_t days = epochTimeY2K /= SECONDS_PER_DAY;

		// Convert days since epoch to year, month, day
		uint16_t year = calcYear(&days);
		// Find the month and day
		uint8_t month = calcMonth(&days, year);
		uint8_t day = days + 1; // Days start from 0, so add 1


		// Get the UTC offset based on whether daylight saving time (DST) is in effect
		return getUTCOffset(year, month, day);
}

// Function to convert epoch time to Time structure (for Berlin timezone with DST consideration)
Time _getTime(time_t timeValue) {

 int8_t UTC_offset = calcUTCOffset(timeValue);
 
 // Convert epoch time to local time in Berlin
 timeValue += UTC_offset * 3600; // Adjust for UTC offset

 // Calculate time components again after adjusting for UTC offset
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

 // Construct and return the Time structure
 Time berlinTime = {year, month, day, hours, minutes, seconds};
 return berlinTime;
}