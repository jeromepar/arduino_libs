#include "LiquidCrystal_I2C.h""

LiquidCrystal_I2C Lcd(0x27, 18, 2); // set the LCD address to 0x27 for a 18 chars and 2 line display

int x = 0;

void setup()
{
	Lcd.init();
	Lcd.backlight();
	Lcd.printCentered(0, "Ready!");
}


// The loop function is called in an endless loop
void loop()
{
	Lcd.clearLine(0);
	Lcd.setCursor(0, 0);
	Lcd.myPrintLong(millis(),10);

	delay(500);
	x++;
}
