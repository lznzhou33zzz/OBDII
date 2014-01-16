/*
 * CanIf_Cbk.h
 *
 *  Created on: 2013Äê12ÔÂ19ÈÕ
 *      Author: zzz
 */
#ifndef CANIF_CBK_H_
#define CANIF_CBK_H_

void L_Data_Confirm(
		Confirm_type *CurrentConfirm);

void L_Data_Indication(
		CanBuffer_type * CurrentRxData);

void L_Remote_Confirm(
		ID_type Identifier,
		Transfer_Status_type Tx_Status);

void L_Remote_Indication(
		RemoteBuffer_type *CurrentTxRemote);
#endif
