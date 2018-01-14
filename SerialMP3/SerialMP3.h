#ifndef SERIALMP3_H
#define SERIALMP3_H

/*
 * SerialMP3.h - y???? todo library
 * J. Parisot
*/

#include <SoftwareSerial.h>



class SerialMP3
{
	public:
		SerialMP3(int arduino_RX, int arduino_TX);
		void init();
		bool available();
		void sendMP3Command(char c);
		String decodeMP3Answer(); //does not work on every hardware
		void sleep();
		void wakeUp();
		void playSong(int folderIndex, int songIndex, int volume); /* volume between 0 & 31 */
		void stop();
	private:
		void sendCommand(int8_t command, int16_t dat);
		String sbyte2hex(uint8_t b);
		String sanswer(uint8_t ansbuf[]);

		SoftwareSerial *mp3Serial;
};

/************ Command byte **************************/
#define CMD_NEXT_SONG     0X01  // Play next song.
#define CMD_PREV_SONG     0X02  // Play previous song.
#define CMD_PLAY_W_INDEX  0X03  //play song + file index in arg
#define CMD_VOLUME_UP     0X04
#define CMD_VOLUME_DOWN   0X05
#define CMD_SET_VOLUME    0X06 //lim 30? + vol in arg

#define CMD_SNG_CYCL_PLAY 0X08  // Single Cycle Play. + file index in arg
#define CMD_SEL_DEV       0X09  // select device storage : 2 = SD card
#define CMD_SLEEP_MODE    0X0A
#define CMD_WAKE_UP       0X0B
#define CMD_RESET         0X0C
#define CMD_PLAY          0X0D
#define CMD_PAUSE         0X0E
#define CMD_PLAY_FOLDER_FILE 0X0F // Play + args 8MSB : folder index - 8LSB file index

#define CMD_STOP_PLAY     0X16
#define CMD_FOLDER_CYCLE  0X17 //same as CMD_SNG_CYCL_PLAY but 8MSB = folder index
#define CMD_SHUFFLE_PLAY  0x18
#define CMD_SET_SNGL_CYCL 0X19 // Set single cycle. arg 0=start, 1=stop

#define CMD_SET_DAC 0X1A	//manage DAC output, with DAC_ON & DAC_OFF
#define DAC_ON  0X00
#define DAC_OFF 0X01

#define CMD_PLAY_W_VOL    0X22 //same as CMD_PLAY_W_INDEX but 8MSB = volume
#define CMD_PLAYING_N     0x4C

/* the following cmds don't work on every hardware */
#define CMD_QUERY_STATUS      0x42
#define CMD_QUERY_VOLUME      0x43
#define CMD_QUERY_FLDR_TRACKS 0x4e
#define CMD_QUERY_TOT_TRACKS  0x48
#define CMD_QUERY_FLDR_COUNT  0x4f

/************ Options **************************/
#define DEV_TF            0X02 // use SD card

#endif
