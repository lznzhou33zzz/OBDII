/*
/*
 * CanIf_Cbk.h
 *
 *  Created on: 2013Äê12ÔÂ19ÈÕ
 *      Author: zzz
 */
#ifndef CANIF_CBK_H_
#define CANIF_CBK_H_

void L_Data_Confirm(
		L_SDU_DataCfm_type CurrentConfirm);

void L_Data_Indication(
		L_SDU_DataInd_type  CurrentRxData);

void L_Remote_Confirm(
		L_SDU_RemoteCfm_type CurrentConfirm);

void L_Remote_Indication(
		L_SDU_RemoteInd_type CurrentTxRemote);
#endif
