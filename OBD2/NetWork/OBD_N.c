/*
 * OBD_N.c
 *
 *  Created on: 2013Äê10ÔÂ19ÈÕ
 *      Author: zzz
 */
#include "Common.h"
#include "OBD_N.h"
#include "DataLink.h"

unsigned char FlowCtrlStart = 0;
enum {
	idle,
	sendFirstFrame,
	waitFlowCtrlFrame,
	sendConsecutiveFrame,
	finishFlow,
}NetworkLayerFlowState;



/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void NetworkLayerSenderFlowctrl()
{
	N_PDU_type current_pdu;
	unsigned short i;
	while(1){
		switch(NetworkLayerFlowState)
		{
		case idle:
			if(FlowCtrlStart == TRUE)
				NetworkLayerFlowState = sendFirstFrame;
			break;
		case sendFirstFrame:
			L_Data_Request();//FF N_PDU
			//wait until(stateOfCAN == SuccessSend , N_As )
			if()//no timeout
			{
				L_Data_Confirm(1,Complete);//1 = ID
				NetworkLayerFlowState = waitFlowCtrlFrame;
			}
			else
			{
				L_Data_Confirm(1,Not_Complete);//1 = ID
				NetworkLayerFlowState = waitFlowCtrlFrame;
			}
			break;
		case waitFlowCtrlFrame:
			//wait until(stateOfCAN == SuccessReceive , N_Bs )
			if()//no timeout
			{
				L_Data_Indication();//FF N_PDU
				NetworkLayerFlowState = sendConsecutiveFrame;
			}
			else
			{
			}
			break;
		case sendConsecutiveFrame:
			for(i = 0 ; i < 1 ; i++)//1 = BS
			{
				L_Data_Request();//FC N_PDU
				//wait until(stateOfCAN == SuccessSend , N_As )
				if()//no timeout
				{
					L_Data_Confirm(1,Complete);//1 = ID
					NetworkLayerFlowState = waitFlowCtrlFrame;
				}
				else
				{
					L_Data_Confirm(1,Not_Complete);//1 = ID
					NetworkLayerFlowState = finishFlow;
				}
			}
			NetworkLayerFlowState = finishFlow;
			break;
		case finishFlow:
			if()
				NetworkLayerFlowState = idle;
			else
				;
			break;
		default:
			break;
		}
	}
}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */



/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void PDU2DataLinkParameter(
		N_PDU_type * current_pdu,
		DataLinkParameter_type * current_DataLinkParameter)
{
	short i;
	switch(current_pdu->N_AI.AddressType){
	case normal_address:
		//1. Set ID
//		if(current_pdu->N_AI.N_TAtype == phyiscal){
//			current_DataLinkParameter->ID = (current_pdu->N_AI.N_SA
//			|=((unsigned long)current_pdu->N_AI.N_TA) << 8
//			|=((unsigned long)0xDA<<16)
//			|=((unsigned long)0x18<<24)
//					);
//		}
//		else if(current_pdu->N_AI.N_TAtype == functional){
//			current_DataLinkParameter->ID = (current_pdu->N_AI.N_SA
//			|=((unsigned long)current_pdu->N_AI.N_TA) << 8
//			|=((unsigned long)0xDB<<16)
//			|=((unsigned long)0x18<<24)
//					);
//		}
//		else
//		{;}
		//2. Set DLC
		current_DataLinkParameter->DLC = 8;
		//3. Set Data
		switch (current_pdu->N_PCI.PCIType){
		case SF:
			current_DataLinkParameter->DATA[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			for(i = 1; i < 8; i++)
				current_DataLinkParameter->DATA[i] = current_pdu->N_DATA.Nml_SF_Data[i-1];
			break;
		case FF:
			current_DataLinkParameter->DATA[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->DATA[1] = current_pdu->N_PCI.PCI.BYTE.byte2;
			for(i = 2; i < 8; i++)
				current_DataLinkParameter->DATA[i] = current_pdu->N_DATA.Nml_SF_Data[i-2];
			break;
		case CF:
			current_DataLinkParameter->DATA[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			for(i = 1; i < 8; i++)
				current_DataLinkParameter->DATA[i] = current_pdu->N_DATA.Nml_SF_Data[i-1];
			break;
		case FC:
			current_DataLinkParameter->DATA[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->DATA[1] = current_pdu->N_PCI.PCI.BYTE.byte2;
			current_DataLinkParameter->DATA[2] = current_pdu->N_PCI.PCI.BYTE.byte3;
			for(i = 3; i < 8; i++)
					current_DataLinkParameter->DATA[i] = current_pdu->N_DATA.Nml_SF_Data[i-3];
			break;
		}
		break;
	case normal_fixed_address:
		//1. Set ID
		if(current_pdu->N_AI.N_TAtype == phyiscal){
			current_DataLinkParameter->ID = (current_pdu->N_AI.N_SA
			|=((unsigned long)current_pdu->N_AI.N_TA) << 8
			|=((unsigned long)0xDA<<16)
			|=((unsigned long)0x18<<24)
					);
		}
		else if(current_pdu->N_AI.N_TAtype == functional){
			current_DataLinkParameter->ID = (current_pdu->N_AI.N_SA
			|=((unsigned long)current_pdu->N_AI.N_TA) << 8
			|=((unsigned long)0xDB<<16)
			|=((unsigned long)0x18<<24)
					);
		}
		else
		{;}
		//2. Set DLC
		current_DataLinkParameter->DLC = 8;
		//3. Set Data
		switch (current_pdu->N_PCI.PCIType){
		case SF:
			current_DataLinkParameter->DATA[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			for(i = 1; i < 8; i++)
				current_DataLinkParameter->DATA[i] = current_pdu->N_DATA.Nml_SF_Data[i-1];
			break;
		case FF:
			current_DataLinkParameter->DATA[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->DATA[1] = current_pdu->N_PCI.PCI.BYTE.byte2;
			for(i = 2; i < 8; i++)
				current_DataLinkParameter->DATA[i] = current_pdu->N_DATA.Nml_SF_Data[i-2];
			break;
		case CF:
			current_DataLinkParameter->DATA[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			for(i = 1; i < 8; i++)
				current_DataLinkParameter->DATA[i] = current_pdu->N_DATA.Nml_SF_Data[i-1];
			break;
		case FC:
			current_DataLinkParameter->DATA[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->DATA[1] = current_pdu->N_PCI.PCI.BYTE.byte2;
			current_DataLinkParameter->DATA[2] = current_pdu->N_PCI.PCI.BYTE.byte3;
			for(i = 3; i < 8; i++)
					current_DataLinkParameter->DATA[i] = current_pdu->N_DATA.Nml_SF_Data[i-3];
			break;
		}
		break;
	case extended_address:
		//1. Set ID
		//2. Set DLC
		current_DataLinkParameter->DLC = 8;
		//3. Set Data
		current_DataLinkParameter->DATA[0] = current_pdu->N_AI.N_TA;
		switch (current_pdu->N_PCI.PCIType){
		case SF:
			current_DataLinkParameter->DATA[1] = current_pdu->N_PCI.PCI.BYTE.byte1;
			for(i = 2; i < 8; i++)
				current_DataLinkParameter->DATA[i] = current_pdu->N_DATA.Nml_SF_Data[i-2];
			break;
		case FF:
			current_DataLinkParameter->DATA[1] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->DATA[2] = current_pdu->N_PCI.PCI.BYTE.byte2;
			for(i = 3; i < 8; i++)
				current_DataLinkParameter->DATA[i] = current_pdu->N_DATA.Nml_SF_Data[i-3];
			break;
		case CF:
			current_DataLinkParameter->DATA[1] = current_pdu->N_PCI.PCI.BYTE.byte1;
			for(i = 2; i < 8; i++)
				current_DataLinkParameter->DATA[i] = current_pdu->N_DATA.Nml_SF_Data[i-2];
			break;
		case FC:
			current_DataLinkParameter->DATA[1] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->DATA[2] = current_pdu->N_PCI.PCI.BYTE.byte2;
			current_DataLinkParameter->DATA[3] = current_pdu->N_PCI.PCI.BYTE.byte3;
			for(i = 4; i < 8; i++)
					current_DataLinkParameter->DATA[i] = current_pdu->N_DATA.Nml_SF_Data[i-4];
			break;
		}
		break;
	case mixed_address:
		//1. Set ID
		if(current_pdu->N_AI.N_TAtype == phyiscal){
			current_DataLinkParameter->ID = (current_pdu->N_AI.N_SA
			|=((unsigned long)current_pdu->N_AI.N_TA) << 8
			|=((unsigned long)0xCD<<16)
			|=((unsigned long)0x18<<24)
					);
		}
		else if(current_pdu->N_AI.N_TAtype == functional){
			current_DataLinkParameter->ID = (current_pdu->N_AI.N_SA
			|=((unsigned long)current_pdu->N_AI.N_TA) << 8
			|=((unsigned long)0xCE<<16)
			|=((unsigned long)0x18<<24)
					);
		}
		else
		{;}
		//2. Set DLC
		current_DataLinkParameter->DLC = 8;
		//3. Set Data
		current_DataLinkParameter->DATA[0] = current_pdu->N_AI.N_AE;
		switch (current_pdu->N_PCI.PCIType){
		case SF:
			current_DataLinkParameter->DATA[1] = current_pdu->N_PCI.PCI.BYTE.byte1;
			for(i = 2; i < 8; i++)
				current_DataLinkParameter->DATA[i] = current_pdu->N_DATA.Nml_SF_Data[i-2];
			break;
		case FF:
			current_DataLinkParameter->DATA[1] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->DATA[2] = current_pdu->N_PCI.PCI.BYTE.byte2;
			for(i = 3; i < 8; i++)
				current_DataLinkParameter->DATA[i] = current_pdu->N_DATA.Nml_SF_Data[i-3];
			break;
		case CF:
			current_DataLinkParameter->DATA[1] = current_pdu->N_PCI.PCI.BYTE.byte1;
			for(i = 2; i < 8; i++)
				current_DataLinkParameter->DATA[i] = current_pdu->N_DATA.Nml_SF_Data[i-2];
			break;
		case FC:
			current_DataLinkParameter->DATA[1] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->DATA[2] = current_pdu->N_PCI.PCI.BYTE.byte2;
			current_DataLinkParameter->DATA[3] = current_pdu->N_PCI.PCI.BYTE.byte3;
			for(i = 4; i < 8; i++)
				current_DataLinkParameter->DATA[i] = current_pdu->N_DATA.Nml_SF_Data[i-4];
			break;
		}
		break;
	default:
		break;
	}
}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */






/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_USDataRequest(
		DATA_Request_type ){

}


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_USDataConfirm(
		DATA_Confirm_type ){

}


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_USDataFFIndication(
		DATA_FF_Indication_type){

}



/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_USDataIndication(
		DATA_Indication_type ){

}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_ChangeParameterRequest(
		DATA_FF_Request_type ){

}


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_ChangePatameterConfirm(
		Change_Para_Confirm_type ){

}
