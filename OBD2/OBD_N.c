/*
 * OBD_N.c
 *
 *  Created on: 2013��10��19��
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
			if()
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
	switch(current_pdu->N_AI.AddressType){
	case normal_address:
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
		break;
	case extended_address:
		current_DataLinkParameter->DATA[0] = current_pdu->N_AI.N_TA;
		break;
	case mixed_address:


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
void FlowCtrlCallBack(N_PDU_type * current_pdu,DataLinkParameter_type * current_DataLinkParameter){

}
