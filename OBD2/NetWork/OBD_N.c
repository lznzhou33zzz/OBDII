/*
 * OBD_N.c
 *
 *  Created on: 2013Äê10ÔÂ19ÈÕ
 *      Author: zzz
 */
#include "Common.h"
#include "OBD_N.h"


unsigned char FlowCtrlStart = 0;
enum {
	idle,
	sendFirstFrame,
	waitFlowCtrlFrame,
	sendConsecutiveFrame,
	finishFlow,
}NetworeLayerFlowState;


unsigned short SendFirstFrame();
void SendConsecutiveFrame();
void DisposeFlowCtrlFrame();
void DisposeException();
void FlowCtrlCallBack();



/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void NetworkLayer_Flow_ctrl()
{
	while(1){
		switch(NetworeLayerFlowState)
		{
		case idle:
			if(FlowCtrlStart == TRUE)
				NetworeLayerFlowState = sendFirstFrame;
			break;
		case sendFirstFrame:
			SendFirstFrame();
			if()//Send success
				NetworeLayerFlowState = waitFlowCtrlFrame;
			else
				;
			break;
		case waitFlowCtrlFrame:
			if()
				NetworeLayerFlowState = sendConsecutiveFrame;
			else
				;
			break;
		case sendConsecutiveFrame:
			//send consecutive frame
			if()
				NetworeLayerFlowState = waitFlowCtrlFrame;
			else
				NetworeLayerFlowState = finishFlow;
			break;
		case finishFlow:
			if()
				NetworeLayerFlowState = idle;
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
NetLayerErrorType SendFirstFrame(){

}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void SendConsecutiveFrame(){

}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void DisposeFlowCtrlFrame(){

}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void DisposeException(){

}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void FlowCtrlCallBack(){

}


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void PDU2DataLinkParameter(N_PDU_type * current_pdu,DataLinkParameter_type * current_DataLinkParameter){
	short i;
	switch(current_pdu->N_AI.AddressType){
	case normal_address:
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
		current_DataLinkParameter->DATA[0] = current_pdu->N_AI.N_TA;
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
		switch (current_pdu->N_PCI.PCIType){
		case SF:
			current_DataLinkParameter->DATA[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			break;
		case FF:
			current_DataLinkParameter->DATA[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->DATA[1] = current_pdu->N_PCI.PCI.BYTE.byte2;
			break;
		case CF:
			current_DataLinkParameter->DATA[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			break;
		case FC:
			current_DataLinkParameter->DATA[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->DATA[1] = current_pdu->N_PCI.PCI.BYTE.byte2;
			current_DataLinkParameter->DATA[2] = current_pdu->N_PCI.PCI.BYTE.byte3;
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
void FlowCtrlCallBack(N_PDU_type * current_pdu,
		DataLinkParameter_type * current_DataLinkParameter){

}





/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_USDataRequest(Message_type Mtype,
					unsigned char N_SA,
					unsigned char N_TA,
					Address_type N_TAtype,		//network address type
					unsigned char N_AE,			//network address extension
					unsigned char *MessageDat,
					unsigned short Length){

}


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_USDataConfirm(Message_type Mtype,
					unsigned char N_SA,
					unsigned char N_TA,
					Address_type N_TAtype,
					unsigned char N_AE,
					N_Result_type N_Result){

}


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_USDataFFIndication(Message_type Mtype,
						unsigned char N_SA,
						unsigned char N_TA,
						Address_type N_TAtype,		//network address type
						unsigned char N_AE,			//network address extension
						unsigned char *MessageData,
						unsigned short Length){

}



/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_USDataIndication(Message_type Mtype,
						unsigned char N_SA,
						unsigned char N_TA,
						Address_type N_TAtype,		//network address type
						unsigned char N_AE,			//network address extension
						unsigned char *MessageData,
						unsigned short Length,
						N_Result_type N_Result){

}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_ChangeParameterRequest(Message_type Mtype,
							unsigned char N_SA,
							unsigned char N_TA,
							Address_type N_TAtype,		//network address type
							unsigned char N_AE,
							Parameter_type Parameter,
							unsigned char Parameter_Value){

}


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_ChangePatameterConfirm(Message_type Mtype,
							unsigned char N_SA,
							unsigned char N_TA,
							Address_type N_TAtype,		//network address type
							unsigned char N_AE,
							Parameter_type Parameter,
							Result_ChangeParameter_type Result_ChangeParameter){

}
