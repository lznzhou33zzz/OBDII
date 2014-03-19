/*
/*
 * CanIf.h
 *
 *  Created on: 2013Äê12ÔÂ19ÈÕ
 *      Author: zzz
 */


#ifndef CANIF_H_
#define CANIF_H_

#include "CanIf_Cfg.h"
#include  "CanIf_Types.h"

#define SendSuccess		1
#define SendFail		0


void L_Data_Request(L_SDU_DataReq_type  CurrentTxData);



void L_Remote_Request (L_SDU_RemoteReq_type CurrentRxRemote);







#endif /* CANIF_H_ */
