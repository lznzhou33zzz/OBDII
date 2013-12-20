/*
 * LLC.c
 * logical link control
 *
 *  Created on: 2013Äê11ÔÂ14ÈÕ
 *      Author: zezhongzhao
 *
 *  Acceptance filtering
 *  overload notification
 *  recovery management
 */



/*
 * **************************************************
 * Application	*
 * layer		*
 * **************************************************
 * Network		*
 * layer		*
 * **************************************************
 * 	Data		*  LLC:logical link control			*
 * 	link		*************************************
 * 	layer		*  MAC:medium access control		*
 * **************************************************
 * 				*  PLS:physical signalling			*
 * Physical		*************************************
 * 				*  PMA:physical medium attachment	*
 * 	layer		*************************************
 * 				*  MDI:medium dependent interface	*
 * **************************************************
 */

#include "DataLink.h"
#include "OBD_N.h"
#include "DriverInterface.h"




/*
 * Function:
 * Description:Request for data transfer
 * Parameter:
 * Return:
 *
 */
void L_Data_Request(
		ID_type Identifier,
		Formate_type Format,
		DataLth_type DLC,
		unsigned char (* Data)[64])
{
	unsigned char i;
	CANFrame_Type data;
	data.Identifier = Identifier.whole_ID;
	data.Format = (unsigned char)Format;
	data.DLC = DLC;
	for(i = 0; i < CANLenthTable[DLC]; i++, Data++)
		data[i] = *Data;
	CANSend(data);
};

/*
 * Function:
 * Description:Indication of data transfer
 * Parameter:
 * Return:
 *
 */
void L_Data_Indication(
		ID_type Identifier,
		Formate_type Format,
		DataLth_type DLC,
		unsigned char (* Data)[64])
{};

/*
 * Function:
 * Description:Confirm data transfer
 * Parameter:
 * Return:
 *
 */
void L_Data_Confirm(
		ID_type Identifier,
		Transfer_Status_type Tx_Status)
{};

/*
 * Function:
 * Description:Request for remote data request
 * Parameter:
 * Return:
 *
 */
void L_Remote_Request (
		ID_type Identifier,
		Formate_type Format,
		DataLth_type DLC)
{};

/*
 * Function:
 * Description:Indication of remote data request
 * Parameter:
 * Return:
 *
 */
void L_Remote_Indication(
		ID_type Identifier,
		Formate_type Format,
		DataLth_type DLC)
{};

/*
 * Function:
 * Description:Confirmation remote data request
 * Parameter:
 * Return:
 *
 */
void L_Remote_Confirm(
		ID_type Identifier,
		Transfer_Status_type Tx_Status)
{};
