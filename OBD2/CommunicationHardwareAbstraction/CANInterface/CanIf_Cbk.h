/*
 * CanIf_Cbk.h
 *
 *  Created on: 2013��12��19��
 *      Author: zzz
 */
#ifndef CANIF_CBK_H_
#define CANIF_CBK_H_

void L_Data_Confirm(
		ID_type Identifier,
		Transfer_Status_type Tx_Status);
void L_Remote_Confirm(
		ID_type Identifier,
		Transfer_Status_type Tx_Status);

#endif
