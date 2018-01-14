#include "Arduino.h"
#include "SerialMP3.h"

#define ARDUINO_RX 3  //should connect to TX of the Serial MP3 Player module
#define ARDUINO_TX 6  //connect to RX of the module


SerialMP3 sMP3(ARDUINO_RX,ARDUINO_TX);

//The setup function is called once at startup of the sketch
void setup()
{
	Serial.begin(9600);
	sMP3.init() ;

	delay(500);

	Serial.println("Ready");
}



// The loop function is called in an endless loop
void loop()
{
	  char c = ' ';

	  // If there a char on Serial call sendMP3Command to sendCommand
	  if ( Serial.available() )
	  {
	    c = Serial.read();
	    sMP3.sendMP3Command(c);
	  }

	  // Check for the answer.
	  if (sMP3.available())
	  {
	    Serial.println(sMP3.decodeMP3Answer());
	  }
	  delay(100);

}
