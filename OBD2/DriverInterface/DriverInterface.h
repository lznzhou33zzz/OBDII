/*
 * DriverInterface.h
 *
 *  Created on: 2013Äê12ÔÂ12ÈÕ
 *      Author: zzz
 */

#ifndef DRIVERINTERFACE_H_
#define DRIVERINTERFACE_H_

#define RECEIVED	1

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
	long Identifier;
	char Format;
	char DLC;
	char Data[64];
}CANFrame_Type;

#endif /* DRIVERINTERFACE_H_ */
