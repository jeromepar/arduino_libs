#ifndef CYCLICTIMER_H_
#define CYCLICTIMER_H_


/*
 * CyclicTimer.h - CyclicTimer library
 * J. Parisot
*/

class CyclicTimer
{
	public:
		CyclicTimer(unsigned long delayms_IN);
		bool watch();
	private:
		unsigned long delay;
		unsigned long lastWaking;

};


#endif /* CYCLICTIMER_H_ */
