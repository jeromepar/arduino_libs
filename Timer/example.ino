#include "timer.h"

#define ECHO_PERIOD 1000

void shout() {
	Serial.println("NO!!");
}
Timer timer(&shout);

void setup()
{
  Serial.begin(9600);
  delay(10);

  Serial.println("I AM YOUR FAAAATHEEEEEEER!!");
  timer.start(ECHO_PERIOD);
}

void loop()
{
	delay(5);

	/* Timer management : whatch for the actions */
	if ( timer.watch() == true ) {
		timer.start(ECHO_PERIOD); /* set it anew */
	}
	/* END OF Timer management */
}
