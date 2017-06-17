/*
TimeManagement.h - TimeManagement library
J. Parisot
*/

#ifndef TIME_MANAGEMENT_H
#define TIME_MANAGEMENT_H

/* Useful Constants */
#define SECS_PER_MIN  60
#define SECS_PER_HOUR 3600
#define SECS_PER_DAY  86400
#define SECS_PER_WEEK  604800
#define DAYS_PER_WEEK 7

class TimeManagement
{
	private:
		long time_ref_s;
		unsigned long time_second_ref_ms;

	public:
		TimeManagement();
		bool newSec();
		long setTime(long seconds); //from the start of the week (Moonday 00h00) return the gap in s
		long timeInSec(int day, int hour, int minute, int second);
		char* day();
		int hour();
		int hour12();
		int minute();
		int second();
		long getTime();
};

#endif
