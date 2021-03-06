/*
  TimeManagement.cpp - TimeManagement library
  J. Parisot. 
*/


#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "TimeManagement.h"

//using namespace std;

TimeManagement::TimeManagement() {
time_ref_s=micros()/1000000;
time_second_ref_ms=0;
  
}

bool TimeManagement::newSec(){
	unsigned long compteur_ms=(micros()/1000-time_second_ref_ms);
	//Serial.println(compteur_us);
	if(compteur_ms>1000){
		time_second_ref_ms=(micros()/1000000)*1000;
		return 1;
	}else {
		return 0;
	}
}
long TimeManagement::setTime(long seconds){
	long previous_time_ref_s = time_ref_s;
	//memorisation of the time reference
	time_ref_s=micros()/1000000-seconds;
	time_second_ref_ms=0;
	
	Serial.println("//DEBUG1: setTime called"); //DEBUG1

	return(time_ref_s-previous_time_ref_s);
} //from the start of the week (Moonday 00h00)

char* TimeManagement::day(){
	int day=(((micros()/1000000-time_ref_s)%SECS_PER_WEEK)/(SECS_PER_DAY));
	switch(day)
	{
	case 0:
		return("Monday");
		break;
	case 1:
		return("Tuesday");
		break;
	case 2:
		return("Wednesday");
		break;
	case 3:
		return("Thursday");
		break;
	case 4:
		return("Friday");
		break;
	case 5:
		return("Saturday");
		break;
	case 6:
		return("Sunday");
		break;
	}
	return("Error_not_found");
}

int TimeManagement::hour(){
return(((millis()/1000L-time_ref_s)%SECS_PER_DAY)/(SECS_PER_HOUR));
}
int TimeManagement::hour12(){
return(hour()%12);
}
int TimeManagement::minute(){
return(( ((long)(millis())/1000L-time_ref_s)%SECS_PER_HOUR)/(SECS_PER_MIN));
}
int TimeManagement::second(){
return( ((long)(millis())/1000L-time_ref_s)%(SECS_PER_MIN));
}

long TimeManagement::timeInSec(long day, long hour, long minute, long second){
  long sec=second+60L*(minute+60L*(hour+24L*day));
  return(sec);
}

/* return the time in second */
long TimeManagement::getTime() {
  return((millis()/1000L-time_ref_s));
}
