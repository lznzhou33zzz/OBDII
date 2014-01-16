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
void L_Data_Request(CanBuffer_type * CurrentTxData)
{}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void L_Data_Indication(CanBuffer_type * CurrentRxData)
{}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void L_Data_Confirm(
		Confirm_type *CurrentConfirm)
{}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void L_Remote_Request (
		RemoteBuffer_type *CurrentRxRemote)
{}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void L_Remote_Indication(
		RemoteBuffer_type *CurrentTxRemote)
{}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void L_Remote_Confirm(
		Confirm_type *CurrentConfirm)
{}
