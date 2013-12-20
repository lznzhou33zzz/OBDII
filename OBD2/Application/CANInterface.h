/*
 * DriverInterface.h
 *
 *  Created on: 2013Äê12ÔÂ12ÈÕ
 *      Author: zzz
 */

#ifndef DRIVERINTERFACE_H_
#define DRIVERINTERFACE_H_

#define RECEIVED	1
#define CAN_CHL		0

//CAN IP Version
#define CLASSICAL_CAN		0
#define CAN_FD				1


extern startTimeOut();


#define WaitUntil(a,op,b,timeout)				\
{												\
	startTimeOut(timeout);						\
	while(1)									\
	{											\
		if(a op b) break;						\
		if(getTimeOut()) break;					\
	}											\
}

typedef enum{
	RETURN_OK,
	TIME_OUT,
} InterfaceRetern;
typedef enum{
	SendSuccess,
	SendFail,
} SendState_type;
typedef struct{
	long Identifier;//ID
	unsigned char Format;//Data,Remote
	unsigned char DLC;//Data lenth
	unsigned char Data[64];//data
}CANFrame_Type;
typedef enum{
	timeout,
	waiting
}TimeOutState_type;

InterfaceRetern CANBandrateConfig(unsigned short NBRP,
								  unsigned short NTSEG1,
								  unsigned short NTSEG2,
								  unsigned short NSJW,
								  unsigned short DBRP,
								  unsigned short DTSEG1,
								  unsigned short DTSET2,
								  unsigned short DSJW);

InterfaceRetern CANSend(CANFrame_Type data);


InterfaceRetern CANReceive(unsigned char chl,
						   CANFrame_Type * data,
						   long timeout);

SendState_type getSendState(unsigned char chl);

long startTimeOut(long timeout);

void setTimeOut(TimeOutState_type state);

TimeOutState_type getTimeOut();























#endif /* DRIVERINTERFACE_H_ */
