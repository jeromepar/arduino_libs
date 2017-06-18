#include "Arduino.h"
#include "CyclicTimer.h"

CyclicTimer every10s(10000);
CyclicTimer every5s(5000);

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(9600);
}



// The loop function is called in an endless loop
void loop()
{
	if(every10s.watch())
	{
		Serial.println("periodic action 10s");
	}

	if(every5s.watch())
	{
		Serial.println("periodic action 5s");
	}

}
