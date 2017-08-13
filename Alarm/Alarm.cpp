#if ARDUINO >= 100
	#include <Arduino.h> 
#else
	#include <WProgram.h> 
#endif

#include "Alarm.h"

 Alarm::Alarm(){
    state=0;
    nbrMaxRepetition=2;
    nbrRepetition=0;
    value=0;
    delayValue=5*60; //5mn
    currentValue=0;
    activated = 0;
}
  void Alarm::disable(){
    state=0;
  }
  void Alarm::enable(){
    state=1;
  }
  int Alarm::getState(){
    return(state);
  }
  
void Alarm::setValue(long sec){
    value=sec;    
    currentValue=value;
}

void Alarm::setValue(int hour, int minute){
	setValue(timeInSec(hour,minute));
}

void Alarm::setDelayValue(long sec){
	delayValue=sec;
}

void Alarm::stopAlarm(){
	currentValue=value;
	nbrRepetition=0;
}

void Alarm::delayAlarm(){
	if (nbrRepetition>nbrMaxRepetition) //every minutes, get UP!
	{
		currentValue=currentValue+60; 
	} else
	{
		currentValue+=delayValue;//ring every delayValue sec until nbr max of repetition
		nbrRepetition=+1;
	}
}

bool Alarm::is_ringing(long currentTime,long maxSecRinging){
  if((state==0) || ((currentTime%SECS_PER_DAY)<currentValue)) {
    return 0;
  }else if ( (currentTime%SECS_PER_DAY)>=currentValue + maxSecRinging ) { // the application got maxSecRinging sec to query the state. after that time is past
	return 0;
  }else {
    return 1;
  }
}
  
long Alarm::timeInSec(int hour, int minute){
  long sec=(long)60*((long)minute+(long)60*(long)hour);
  return(sec);
}
