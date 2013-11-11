/*
 * OBD.c
 *
 *  Created on: 2013Äê10ÔÂ14ÈÕ
 *      Author: zzz
 */
#include "Common.h"
#include "OBD_DL.h"

typedef enum{
	StateA,
	StateB,
	StateC,
	StateD,
	StateE,
	StateF
}IniReturnType;


typedef enum{
	setBautrate,
	transmit,
	waitResponse,
	transmitDone,
	errorDetaction,
	judgmentCAN11InitEnd,
	resetBautrateAndRetry,
	transmitError,
}CAN11InitReqState_Type;



IniReturnType init_state;
char Init_sequence(void){
	do{
		/*--------1. 11bit request --------------*/
		if(init_state == StateA)
		{init_state = CAN11IdentifierReq();}
		/*--------2. wait 11bit response --------*/
		if(init_state == StateB)
		{init_state = CAN11IdentifierResq();}
		/*--------3. 29bit request --------------*/
		if(init_state == StateC)
		{init_state = CAN29IdentifierReq();}
		/*--------4. wait 29bit response --------*/
		if(init_state == StateD)
		{init_state = CAN11IdentifierResq();}
	}while(init_state != StateE || init_state != StateF);
}


IniReturnType CAN11IdentifierReq(void)
{
	CAN11InitReqState_Type state;
	state = setBautrate;
	do{
		/*----setup baudrate --------------------------*/
		if(state == setBautrate)
		{
			;
		}
		/*----Transmit functional request CAN identifier
			  service $01,PID`s supported request message
			  as specified in ISO 15031-5--------------*/
		if(state == transmit)
		{
			;
		}
		/**/
		if(state == waitResponse)
		{
			;
		}
		/**/
		if(state == errorDetaction)
		{
			;
		}
		/**/
		if(state == judgmentCAN11InitEnd)
		{
			;
		}
		/*----Disconnect from CAN bus reset CAN
		 	  controller------------------------------*/
		if(state == resetBautrateAndRetry)
		{
			;
		}
	}while(state == transmitDone || state == transmitError);
	if(state == transmitDone){
		return StateB;
	}
	else{
		return StateF;
	}
}

IniReturnType CAN11IdentifierResp(void)
{



	return StateE;
}

IniReturnType CAN29IdentifierReq(void)
{



	return StateE;
}

IniReturnType CAN29IdentifierResp(void)
{



	return StateE;
}

