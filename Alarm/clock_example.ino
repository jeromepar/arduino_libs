#include "TimeManagement.h"
#include "Alarm.h"

#define PIN_ALARM 13

  TimeManagement tm;
  Alarm alarm;

void setup()
{
  Serial.begin(9600);
  delay(10);

  tm.setTime(tm.timeInSec(6,10,29,50));
  alarm.setValue(10,30);
  alarm.enable();
}

void loop()
{
  delay(5);
  if(tm.newSec()) {
    Serial.print("It is: ");
    Serial.print(tm.hour());
    Serial.print("h");
    Serial.print(tm.minute());
    Serial.print(" and ");
    Serial.print(tm.second());
    Serial.println(" seconds");
    Serial.print("Day: ");
    Serial.println(tm.day());

    if(tm.second()==0) {
		if(alarm.is_ringing(tm.getTime())){
			  digitalWrite(PIN_ALARM,HIGH);
			  Serial.println("RINGING!!!");
			  delay(2000);
			  digitalWrite(PIN_ALARM,LOW);
			  Serial.println("OFF.");
		}else{
		  digitalWrite(PIN_ALARM,LOW);
		}
    }
  }
}
