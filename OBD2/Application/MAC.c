/*
 * MAC.c
 *
 *  Created on: 2013Äê11ÔÂ14ÈÕ
 *      Author: zezhongzhao
 *
 *  Data encapsulation/decapsulation
 *  Frame coding(stuffing,destuffing)
 *  medium access management
 *  error detection
 *  error signalling
 *  acknowledgement
 *  serialization/deserialization
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


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void MA_Data_Request(
		ID_type Identifier,
		Formate_type Format,
		DataLth_type DLC,
		unsigned char *Data)
{};


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void MA_Data_Indication(
		ID_type Identifier,
		Formate_type Format,
		DataLth_type DLC,
		unsigned char *Data)
{}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void MA_Data_Confirm(
		ID_type Identifier,
		Transfer_Status_type Transmission_Status)
{}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void MA_Remote_Request(
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
void MA_Remote_Indication(
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
void MA_Remote_Confirm(
		ID_type Identifier,
		Transfer_Status_type Transmission_Status)
{}


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void MA_OVLD_Request()
{}



/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void MA_OVLD_Indication()
{}




/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void MA_OVLD_Confirm(
		Transfer_Status_type Transmission_Status)
{}






