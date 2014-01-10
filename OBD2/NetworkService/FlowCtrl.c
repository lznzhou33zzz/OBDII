/*
 * FlowCtrl.c
 *
 *  Created on: 2014Äê1ÔÂ10ÈÕ
 *      Author: zezhongzhao
 */
#include "FlowCtrl.h"
#include "Common.h"
/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void NetworkLayerFlowctrl()
{
	N_PDU_type current_pdu;
	unsigned short i;
	unsigned char chl;

	switch(NetworkLayerFlowState)
	{
	case idle:
		if(FlowCtrlStart == TRUE)
			NetworkLayerFlowState = sendFirstFrame;
		break;
	case sendFirstFrame:
		L_Data_Request();//FF N_PDU
		WaitUntil(getSendState(chl),==,SendSuccess,100);//wait until(stateOfCAN == SuccessSend , N_As )
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
