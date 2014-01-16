/*
 * CanIf_Cfg.h
 *
 *  Created on: 2013Äê12ÔÂ19ÈÕ
 *      Author: zzz
 */

#ifndef CANIF_CFG_H_
#define CANIF_CFG_H_


#define RECEIVED	1
#define CAN_CHL		0

//CAN IP Version
#define CLASSICAL_CAN		0
#define CAN_FD				1


void L_Data_Indication(
		CanBuffer_type * CurrentRxBuffer);

void L_Data_Confirm(
		ID_type Identifier,
		Transfer_Status_type Tx_Status);
#endif /* CANIF_CFG_H_ */
