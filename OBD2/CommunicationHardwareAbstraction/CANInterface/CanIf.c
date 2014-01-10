/*
 * CanIf.c
 *
 *  Created on: 2013Äê12ÔÂ19ÈÕ
 *      Author: zzz
 */

#include "CanIf.h"
#include "CanIf_Cbk.h"


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void L_Data_Request(
		ID_type Identifier,
		Formate_type Format,
		DataLth_type DLC,
		unsigned char (* Data)[64])
{}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void L_Data_Indication(
		ID_type Identifier,
		Formate_type Format,
		DataLth_type DLC,
		unsigned char (* Data)[64])
{}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void L_Data_Confirm(
		ID_type Identifier,
		Transfer_Status_type Tx_Status)
{}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void L_Remote_Request (
		ID_type Identifier,
		Formate_type Format,
		DataLth_type DLC)
{}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void L_Remote_Indication(
		ID_type Identifier,
		Formate_type Format,
		DataLth_type DLC)
{}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void L_Remote_Confirm(
		ID_type Identifier,
		Transfer_Status_type Tx_Status)
{}
