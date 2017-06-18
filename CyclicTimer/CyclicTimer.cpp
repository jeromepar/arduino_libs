/*
 * CyclicTimer.cpp
 *
 *  Created on: 18 juin 2017
 *      Author: Jerome
 */

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "CyclicTimer.h"


CyclicTimer::CyclicTimer(unsigned long delayms_IN){
	delay = delayms_IN;
	lastWaking = 0;
}

boolean CyclicTimer::watch(){
	unsigned long time = millis();
	if (time-lastWaking > delay){
		lastWaking= time;
		return true;
	} else {
		return false;
	}
}


