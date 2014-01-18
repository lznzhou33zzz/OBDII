/*
 * Common.h
 *
 *  Created on: 2013Äê11ÔÂ1ÈÕ
 *      Author: zzz
 */

#ifndef COMMON_H_
#define COMMON_H_

#define TRUE				1
#define FALSE				0
#define SUPPORTED			1
#define NOT_SUPPORT			0
#define RECEIVED			1
#define NOT_RECEIVED		0



#define WaitUntil(a,op,b,timeout)				\
{												\
	startTimeOut(timeout);						\
	while(1)									\
	{											\
		if(a op b) break;						\
		if(getTimeOut()) break;					\
	}											\
}


#endif /* COMMON_H_ */
