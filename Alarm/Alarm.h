#ifndef ALARM_H
#define ALARM_H

#define SECS_PER_WEEK  604800
#define SECS_PER_DAY   86400


class Alarm
{
  public:
	  Alarm();
	  void disable();
	  void enable();
	  int getState();
	  void setValue(long sec);
	  void setValue(int hour, int minute);
	  void setDelayValue(long sec);
	  void stopAlarm();
	  void delayAlarm();
	  bool is_ringing(long currentTime, long maxSecRinging);
	  
  private:
	  int activated;
	  int state;
	  int nbrRepetition;
	  int nbrMaxRepetition;
	  long value;
	  long currentValue;
	  long delayValue;
	  long timeInSec(int hour, int minute);
};

#endif
