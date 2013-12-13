/*
 * DriverInterface.c
 *
 *  Created on: 2013Äê12ÔÂ12ÈÕ
 *      Author: zzz
 */
#include "DriverInterface.h"
#include "Common.h"

typedef enum{
	timeout,
	waiting
}TimeOutState_type;


static TimeOutState_type TimeOutState;
char CANLenthTable [16] = (0,1,2,3,4,5,6,7,8,12,16,20,24,32,48,64);



/*---------------------- CAN about -------------------------*/
InterfaceRetern CANChannelConfig(unsigned char chl)
{
	return RETURN_OK;

}



InterfaceRetern CANBandrateConfig(unsigned short NBRP,
								  unsigned short NTSEG1,
								  unsigned short NTSEG2,
								  unsigned short NSJW,
								  unsigned short DBRP,
								  unsigned short DTSEG1,
								  unsigned short DTSET2,
								  unsigned short DSJW)
{
	return RETURN_OK;
}


InterfaceRetern CANSend(unsigned char chl,
			 	 	 	CANFrame_Type data)
{
	return RETURN_OK;
}

InterfaceRetern CANReceive(unsigned char chl,
						   CANFrame_Type * data,
						   long timeout)
{
	char A;//flag of channel receive state
	WaitUntil(A ,== ,RECEIVED,timeout);
	if(isTimeOut() == TRUE){
		return TIME_OUT;
	}
	return RETURN_OK;
}
SendState_type getSendState(unsigned char chl)
{
	volatile SendState_type sendstate;
	sendstate = SendSuccess;
	return sendstate;
}
/*---------------------- CAN about end----------------------*/


/*---------------------- Timer about -----------------------*/
long startTimeOut(long timeout)
{
	//should add driver
}
void setTimeOut(TimeOutState_type state){
	TimeOutState = state;
}
TimeOutState_type getTimeOut()
{
	return TimeOutState;
}

/*---------------------- Timer about end--------------------*/
