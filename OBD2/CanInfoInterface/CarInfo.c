/*
 * CarInfo.c
 *
 *  Created on: 2014Äê3ÔÂ19ÈÕ
 *      Author: zezhongzhao
 */
#include "Std_Types.h"
#include "CarInfo.h"
#include "OBD_N_task.h"

CarInfo_get(InfoType_type info_type)
{
	N_SDU_DataReq_type parameter;
	uint8 data[7];
	data[0] = 0x05;
	switch(info_type)
	{
	case speed:
		parameter.MessageData = data;
		parameter.Mtype = diagnostics;
		parameter.Length = 1;
		parameter.N_AI.N_SA = 0xF1;
		parameter.N_AI.N_TA = 0X33;
		parameter.N_AI.N_TAtype = functional;
		N_USDataRequest(parameter);
		break;
	default:
		break;
	}
}
