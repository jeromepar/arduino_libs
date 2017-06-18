# arduino_libs
Personal Libs developped/adapted for the Arduino


-----------------------

Contains:

- TimeManagement library:
	- Based on arduino micros()
	- provide interfaces to set Time and retreive it
	
- Alarm library: implementation of basics of an alarm clock
	- set alarm
	- enable/disable
	- snooze
	- given current time in sec (from Monday 0AM = 0s), return the alarm state

- LiquidCrystal_I2C:
	- Class alowing to write on a LCD screen through I2C
	- use <Wire.h>

- SimpleFIFO: by Alexander Brevig
	- non volatile allocation
	- dequeue / enqueue features
	- peek feature
	- flush feature

- Timer: Basic timer implementation
	- start / stop features
	- do not use interruption, should be polled to trigger the actions
	
- TiltSensor : easy watch of a digital tilt_sensor
	- detect tilts (debounce fuction)
	- count tilts happening in a row
	
- CyclicTimer : provide an easy way to execute periodic actions
	- provide the test for an "if" function