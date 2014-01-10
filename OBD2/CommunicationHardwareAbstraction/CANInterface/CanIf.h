/*
 * CanIf.h
 *
 *  Created on: 2013Äê12ÔÂ19ÈÕ
 *      Author: zzz
 */
#include "CanIf_Cfg.h"
#include  "CanIf_Types.h"

#ifndef CANIF_H_
#define CANIF_H_




void L_Data_Request(
		ID_type Identifier,
		Formate_type Format,
		DataLth_type DLC,
		unsigned char (* Data)[64]);

void L_Data_Indication(
		ID_type Identifier,
		Formate_type Format,
		DataLth_type DLC,
		unsigned char (* Data)[64]);

void L_Remote_Request (
		ID_type Identifier,
		Formate_type Format,
		DataLth_type DLC);

void L_Remote_Indication(
		ID_type Identifier,
		Formate_type Format,
		DataLth_type DLC);





#endif /* CANIF_H_ */
