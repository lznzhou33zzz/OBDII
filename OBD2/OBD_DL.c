/*
 * OBD.c
 *
 *  Created on: 2013Äê10ÔÂ14ÈÕ
 *      Author: zzz
 */
#include "Common.h"
#include "OBD_DL.h"


enum
{
	ID11_ONLY,
	ID29_ONLY,
	ID11_ID29,
	NO_SUPPROT
}SupportType;
char Init_sequence(void){
	char IsSupport = NOT_SUPPORT;
	char IsID11_recieved,IsID29_received;
	SupportType Support = NO_SUPPROT;

	/*--------1. 11bit request --------*/

	/*--------2. wait 11bit response --------*/

	/*--------3. 29bit request --------*/

	/*--------4. wait 29bit response --------*/

	/*--------5. Judgment --------*/
	 if(IsID29_received == RECEIVED && IsID11_recieved == RECEIVED)
	{
		Support = ID11_ID29;
		IsSupport = SUPPORTED;
		return	IsSupport;
	}
	else if(IsID29_received == NOT_RECEIVED && IsID11_recieved == RECEIVED)
	{
		Support = ID11_ONLY;
		IsSupport = SUPPORTED;
		return	IsSupport;
	}
	else if(IsID29_received == RECEIVED && IsID11_recieved == NOT_RECEIVED)
	{
		Support = ID29_ONLY;
		IsSupport = SUPPORTED;
		return	IsSupport;
	}
	else
	{
		return IsSupport;
	}

}






