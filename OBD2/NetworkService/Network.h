/*
 * Service.h
 *
 *  Created on: 2014Äê1ÔÂ10ÈÕ
 *      Author: zezhongzhao
 */

#ifndef NETWORK_H_
#define NETWORK_H_
#include "Network_Type.h"
#include  "CanIf_Types.h"
#include "Std_Types.h"
#include "Common.h"

#define N_FWTmax
#define TIMEOUT_N_As			1000
#define TIMEOUT_N_Ar			1000
#define TIMEOUT_B_Bs			1000
#define TIMEOUT_N_Cr			1000


//Error about
#define NetLayerErrorType		unsigned short
#define NE_OK					0
#define NE_OVERTIME				1


extern N_Result_type NewSender();
extern inline inline Request_type ReqState_get();
extern void RequestCtrl(N_SDU_Type);
extern void ResponseCtrl(N_SDU_Type);
#endif /* SERVICE_H_ */
