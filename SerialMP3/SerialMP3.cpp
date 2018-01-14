/*
  SerialMP3.h - Y???? todo library
  J. Parisot. 
 */


#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include "SerialMP3.h"

SerialMP3::SerialMP3(int arduino_RX, int arduino_TX) {
	static SoftwareSerial serial(arduino_RX, arduino_TX);
	this->mp3Serial = &serial;
}

void SerialMP3::init() {
	this->mp3Serial->begin(9600);
	delay(500);
	sendCommand(CMD_SEL_DEV, DEV_TF);
}

bool SerialMP3::available() {
	return(this->mp3Serial->available());
}

void SerialMP3::sleep(){
	sendCommand(CMD_SLEEP_MODE, 0x00);
}

void SerialMP3::wakeUp(){
	sendCommand(CMD_WAKE_UP, 0x00);
}

void SerialMP3::playSong(int folderIndex /* todo usefull?? */, int songIndex, int volume){
//	sendCommand(CMD_SET_VOLUME, volume);
//	delay(20);
//	sendCommand(CMD_PLAY_FOLDER_FILE, 0x0101);
	sendCommand(CMD_PLAY_W_VOL, ( (volume << 8) &0xff00 )+(0xff & songIndex));
}

void SerialMP3::stop(){
	sendCommand(CMD_STOP_PLAY, 0x00);
}

void SerialMP3::sendMP3Command(char c){
	switch (c) {
	case '?':
	case 'h':
		Serial.println("HELP  ");
		Serial.println(" p = Play");
		Serial.println(" P = Pause");
		Serial.println(" > = Next");
		Serial.println(" < = Previous");
		Serial.println(" + = Volume UP");
		Serial.println(" - = Volume DOWN");
		Serial.println(" c = Query current file");
		Serial.println(" q = Query status");
		Serial.println(" v = Query volume");
		Serial.println(" x = Query folder count");
		Serial.println(" t = Query total file count");
		Serial.println(" 1 = Play folder 1");
		Serial.println(" 2 = Play folder 2");
		Serial.println(" 3 = same");
		Serial.println(" 4 = same");
		Serial.println(" 5 = same");
		Serial.println(" S = Sleep");
		Serial.println(" W = Wake up");
		Serial.println(" r = Reset");
		break;


	case 'p':
		Serial.println("Play ");
		sendCommand(CMD_PLAY, 0);
		break;

	case 'P':
		Serial.println("Pause");
		sendCommand(CMD_PAUSE, 0);
		break;

	case '>':
		Serial.println("Next");
		sendCommand(CMD_NEXT_SONG, 0);
		sendCommand(CMD_PLAYING_N, 0x0000); // ask for the number of file is playing
		break;

	case '<':
		Serial.println("Previous");
		sendCommand(CMD_PREV_SONG, 0);
		sendCommand(CMD_PLAYING_N, 0x0000); // ask for the number of file is playing
		break;

	case '+':
		Serial.println("Volume Up");
		sendCommand(CMD_VOLUME_UP, 0);
		break;

	case '-':
		Serial.println("Volume Down");
		sendCommand(CMD_VOLUME_DOWN, 0);
		break;

	case 'c':
		Serial.println("Query current file");
		sendCommand(CMD_PLAYING_N, 0);
		break;

	case 'q':
		Serial.println("Query status");
		sendCommand(CMD_QUERY_STATUS, 0);
		break;

	case 'v':
		Serial.println("Query volume");
		sendCommand(CMD_QUERY_VOLUME, 0);
		break;

	case 'x':
		Serial.println("Query folder count");
		sendCommand(CMD_QUERY_FLDR_COUNT, 0);
		break;

	case 't':
		Serial.println("Query total file count");
		sendCommand(CMD_QUERY_TOT_TRACKS, 0);
		break;

	case '1':
		Serial.println("Play folder 1");
		sendCommand(CMD_FOLDER_CYCLE, 0x0101);
		break;

	case '2':
		Serial.println("Play folder 2");
		sendCommand(CMD_FOLDER_CYCLE, 0x0201);
		break;

	case '3':
		Serial.println("Play folder 3");
		sendCommand(CMD_FOLDER_CYCLE, 0x0301);
		break;

	case '4':
		Serial.println("Play folder 4");
		sendCommand(CMD_FOLDER_CYCLE, 0x0401);
		break;

	case '5':
		Serial.println("Play folder 5");
		sendCommand(CMD_FOLDER_CYCLE, 0x0501);
		break;

	case 'S':
		Serial.println("Sleep");
		sendCommand(CMD_SLEEP_MODE, 0x00);
		break;

	case 'W':
		Serial.println("Wake up");
		sendCommand(CMD_WAKE_UP, 0x00);
		break;

	case 'r':
		Serial.println("Reset");
		sendCommand(CMD_RESET, 0x00);
		break;
	}
}

String SerialMP3::decodeMP3Answer(){ //does not work on every hardware
	String decodedMP3Answer = "";

	static uint8_t ansbuf[10] = {0}; // BETTER LOCALLY

	decodedMP3Answer += sanswer(ansbuf);

	switch (ansbuf[3]) {
	case 0x3A:
		decodedMP3Answer += " -> Memory card inserted.";
		break;

	case 0x3D:
		decodedMP3Answer += " -> Completed play num " + String(ansbuf[6], DEC);
		break;

	case 0x40:
		decodedMP3Answer += " -> Error";
		break;

	case 0x41:
		decodedMP3Answer += " -> Data received correctly. ";
		break;

	case 0x42:
		decodedMP3Answer += " -> Status playing: " + String(ansbuf[6], DEC);
		break;

	case 0x48:
		decodedMP3Answer += " -> File count: " + String(ansbuf[6], DEC);
		break;

	case 0x4C:
		decodedMP3Answer += " -> Playing: " + String(ansbuf[6], DEC);
		break;

	case 0x4E:
		decodedMP3Answer += " -> Folder file count: " + String(ansbuf[6], DEC);
		break;

	case 0x4F:
		decodedMP3Answer += " -> Folder count: " + String(ansbuf[6], DEC);
		break;
	}

	return decodedMP3Answer;
}

/********************************************************************************/
/*Function: Send command to the MP3                                         */
/*Parameter:-int8_t command                                                     */
/*Parameter:-int16_ dat  parameter for the command                              */
void SerialMP3::sendCommand(int8_t command, int16_t dat){
	static int8_t Send_buf[8] = {0}; // Buffer for Send commands.
	delay(20);
	Send_buf[0] = 0x7e;   //
	Send_buf[1] = 0xff;   //
	Send_buf[2] = 0x06;   // Len
	Send_buf[3] = command;//
	Send_buf[4] = 0x00;   // 0x00 NO, 0x01 feedback
	Send_buf[5] = (int8_t)(dat >> 8);  //datah
	Send_buf[6] = (int8_t)(dat);       //datal
	Send_buf[7] = 0xef;   //
	Serial.print("Sending: ");
	for (uint8_t i = 0; i < 8; i++)
	{
		mp3Serial->write(Send_buf[i]) ;
		Serial.print(sbyte2hex(Send_buf[i]));
	}
	Serial.println();
}

/********************************************************************************/
/*Function: sbyte2hex. Returns a byte data in HEX format.                 */
/*Parameter:- uint8_t b. Byte to convert to HEX.                                */
/*Return: String                                                                */
String SerialMP3::sbyte2hex(uint8_t b){
	String shex;

	shex = "0X";

	if (b < 16) shex += "0";
	shex += String(b, HEX);
	shex += " ";
	return shex;
}


/********************************************************************************/
/*Function: sanswer. Returns a String answer from mp3 UART module.              */
/*Parameter:- uint8_t ansbuf[] : buff to put data                               */
/*Return: String. If the answer is well formated answer.                        */

String SerialMP3::sanswer(uint8_t ansbuf[])
{
	uint8_t i = 0;
	String mp3answer = "";

	// Get only 10 Bytes
	while (mp3Serial->available() && (i < 10))
	{
		uint8_t b = mp3Serial->read();
		ansbuf[i] = b;
		i++;

		mp3answer += sbyte2hex(b);
	}

	// if the answer format is correct.
	if ((ansbuf[0] == 0x7E) && (ansbuf[9] == 0xEF))
	{
		return mp3answer;
	}

	return "???: " + mp3answer;
}
