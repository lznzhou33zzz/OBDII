/*
 * OBD.c
 *
 *  Created on: 2013Äê10ÔÂ14ÈÕ
 *      Author: zzz
 */
#include "Common.h"
#include "Std_Types.h"
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
typedef enum{
	waitTimeOutOrRecOK,
	judgmentNgtvResp,
	judgmentOtherNgtvResp,
	judgmentRetryElapsed,
	CAN11IDUsed
}CAN11InitRespState_Type;

unsigned char P2CANTimeOut;

IniReturnType init_state;
char Init_sequence(void){
	do{
		/*--------1. 11bit request --------------*/
		if(init_state == StateA)
		{init_state = CAN11IdentifierReq();}
		/*--------2. wait 11bit response --------*/
		if(init_state == StateB)
		{init_state = CAN11IdentifierResp();}
		/*--------3. 29bit request --------------*/
		if(init_state == StateC)
		{init_state = CAN29IdentifierReq();}
		/*--------4. wait 29bit response --------*/
		if(init_state == StateD)
		{init_state = CAN29IdentifierResp();}
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
			state = transmit;
		}
		/*----Transmit functional request CAN identifier
			  service $01,PID`s supported request message
			  as specified in ISO 15031-5--------------*/
		if(state == transmit)
		{

			state = waitResponse;
		}
		/**/
		if(state == waitResponse)
		{
			state = errorDetaction;
		}
		/**/
		if(state == errorDetaction)
		{
			state = judgmentCAN11InitEnd;
		}
		/**/
		if(state == judgmentCAN11InitEnd)
		{
			state = resetBautrateAndRetry;
		}
		/*----Disconnect from CAN bus reset CAN
		 	  controller------------------------------*/
		if(state == resetBautrateAndRetry)
		{
			state = setBautrate;
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
	CAN11InitRespState_Type state;
	char allRespComplete;
	state = waitTimeOutOrRecOK;
	// start P2CAN timer

	//wait response
	do{
		switch(state){
		case waitTimeOutOrRecOK:
			if(P2CANTimeOut == TRUE || allRespComplete == TRUE)
				state = judgmentNgtvResp;
			break;
		case judgmentNgtvResp:


			if()//busyRepeatRequest negative response
				state = judgmentNgtvResp;
			else
				state = judgmentNgtvResp;
			break;
		case judgmentOtherNgtvResp:

			if()//any negative response?
				return StateF;
			else
				state = CAN11IDUsed;
			break;
		case CAN11IDUsed:
			return StateE;
			break;
		case judgmentRetryElapsed:
			if()//Number of retries elapsed
				return StateF;
			else
				return StateA;
			break;
		default:
			break;
		}
	}while(P2CANTimeOut == TRUE);
	return StateC;
}

IniReturnType CAN29IdentifierReq(void)
{



	return StateE;
}

IniReturnType CAN29IdentifierResp(void)
{



	return StateE;
}
a
