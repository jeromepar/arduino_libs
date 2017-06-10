#define SECS_PER_WEEK  604800


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
	  bool is_ringing(long currentTime);
	  
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