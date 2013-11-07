/*
 * OBDII.c
 *
 *  Created on: 2013Äê10ÔÂ2ÈÕ
 *      Author: zezhongzhao
 */

char *
dtc_decode(uint8 *data, uint32 len, uint8 *vehicle, uint8 *ecu, uint32 protocol)
{
	static char buf[1024];
	char area;


		switch ((data[0] >> 6) & 0x03)	/* Top 2 bits are area */
		{
		case 0:
			area = 'P';
			break;
		case 1:
			area = 'C';
			break;
		case 2:
			area = 'B';
			break;
		case 3:
			area = 'U';
			break;
		}
		break;

	return(buf);
}
