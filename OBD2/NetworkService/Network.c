/*
 * Service.c
 *
 *  Created on: 2014Äê1ÔÂ10ÈÕ
 *      Author: zezhongzhao
 */
#include "Network.h"
#include "Common.h"
#include "CanIf.h"
#include "CanIf_Types.h"
#include "Network_Type.h"
#include "Network_Cfg.h"
//macro define

//Public variable

//local variable
Sender_type Sender;
N_SDU_DataReq_type CurReqData;
N_PDU_type  PDU_queue[32];





/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
L_SDU_DataReq_type N_PDU2L_SDU(
		N_PDU_type * Current_pdu)
{
	L_SDU_DataReq_type  current_DataReq;
	short i;


	//1. Set ID
	current_DataReq->Identifier.Ext_ID.OBD.P = default_P;
	current_DataReq->Identifier.Ext_ID.OBD.R = default_R;
	current_DataReq->Identifier.Ext_ID.OBD.DP = default_DP;
	if(Current_pdu->N_AI.N_TAtype == functional
			)
	{
		current_DataReq->Identifier.Ext_ID.OBD.PF = NOR_FIX_FUN_PF;
	}
	else if(Current_pdu->N_AI.N_TAtype == phyiscal
			)
	{
		current_DataReq->Identifier.Ext_ID.OBD.PF = NOR_FIX_PHY_PF;
	}
	else
	{}
	current_DataReq->Identifier.Ext_ID.OBD.PS = Current_pdu->N_AI.N_SA;
	current_DataReq->Identifier.Ext_ID.OBD.SA = Current_pdu->N_AI.N_SA;
	//2. Set DLC
	current_DataReq.DLC = 8;
	//3. Set Data
		switch (Current_pdu->N_PCI.PCIType){
		case SF:
			current_DataLinkParameter->Data[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			for(i = 1; i < 8; i++)
				current_DataLinkParameter->Data[i] = current_pdu->N_DATA.Nml_SF_Data[i-1];
			break;
		case FF:
			current_DataLinkParameter->Data[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->Data[1] = current_pdu->N_PCI.PCI.BYTE.byte2;
			for(i = 2; i < 8; i++)
				current_DataLinkParameter->Data[i] = current_pdu->N_DATA.Nml_SF_Data[i-2];
			break;
		case CF:
			current_DataLinkParameter->Data[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			for(i = 1; i < 8; i++)
				current_DataLinkParameter->Data[i] = current_pdu->N_DATA.Nml_SF_Data[i-1];
			break;
		case FC:
			current_DataLinkParameter->Data[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->Data[1] = current_pdu->N_PCI.PCI.BYTE.byte2;
			current_DataLinkParameter->Data[2] = current_pdu->N_PCI.PCI.BYTE.byte3;
			for(i = 3; i < 8; i++)
					current_DataLinkParameter->Data[i] = current_pdu->N_DATA.Nml_SF_Data[i-3];
			break;
		}

	case normal_fixed_address:
		//1. Set ID
		if(current_pdu->N_AI.N_TAtype == phyiscal){
			current_DataLinkParameter->Identifier = (current_pdu->N_AI.N_SA
			|=((unsigned long)current_pdu->N_AI.N_TA) << 8
			|=((unsigned long)0xDA<<16)
			|=((unsigned long)0x18<<24)
					);
		}
		else if(current_pdu->N_AI.N_TAtype == functional){
			current_DataLinkParameter->Identifier = (current_pdu->N_AI.N_SA
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
			current_DataLinkParameter->Data[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			for(i = 1; i < 8; i++)
				current_DataLinkParameter->Data[i] = current_pdu->N_DATA.Nml_SF_Data[i-1];
			break;
		case FF:
			current_DataLinkParameter->Data[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->Data[1] = current_pdu->N_PCI.PCI.BYTE.byte2;
			for(i = 2; i < 8; i++)
				current_DataLinkParameter->Data[i] = current_pdu->N_DATA.Nml_SF_Data[i-2];
			break;
		case CF:
			current_DataLinkParameter->Data[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			for(i = 1; i < 8; i++)
				current_DataLinkParameter->Data[i] = current_pdu->N_DATA.Nml_SF_Data[i-1];
			break;
		case FC:
			current_DataLinkParameter->Data[0] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->Data[1] = current_pdu->N_PCI.PCI.BYTE.byte2;
			current_DataLinkParameter->Data[2] = current_pdu->N_PCI.PCI.BYTE.byte3;
			for(i = 3; i < 8; i++)
					current_DataLinkParameter->Data[i] = current_pdu->N_DATA.Nml_SF_Data[i-3];
			break;
		}
		break;
	case extended_address:
		//1. Set ID
		//2. Set DLC
		current_DataLinkParameter->DLC = 8;
		//3. Set Data
		current_DataLinkParameter->Data[0] = current_pdu->N_AI.N_TA;
		switch (current_pdu->N_PCI.PCIType){
		case SF:
			current_DataLinkParameter->Data[1] = current_pdu->N_PCI.PCI.BYTE.byte1;
			for(i = 2; i < 8; i++)
				current_DataLinkParameter->Data[i] = current_pdu->N_DATA.Nml_SF_Data[i-2];
			break;
		case FF:
			current_DataLinkParameter->Data[1] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->Data[2] = current_pdu->N_PCI.PCI.BYTE.byte2;
			for(i = 3; i < 8; i++)
				current_DataLinkParameter->Data[i] = current_pdu->N_DATA.Nml_SF_Data[i-3];
			break;
		case CF:
			current_DataLinkParameter->Data[1] = current_pdu->N_PCI.PCI.BYTE.byte1;
			for(i = 2; i < 8; i++)
				current_DataLinkParameter->Data[i] = current_pdu->N_DATA.Nml_SF_Data[i-2];
			break;
		case FC:
			current_DataLinkParameter->Data[1] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->Data[2] = current_pdu->N_PCI.PCI.BYTE.byte2;
			current_DataLinkParameter->Data[3] = current_pdu->N_PCI.PCI.BYTE.byte3;
			for(i = 4; i < 8; i++)
					current_DataLinkParameter->Data[i] = current_pdu->N_DATA.Nml_SF_Data[i-4];
			break;
		}
		break;
	case mixed_address:
		//1. Set ID
		if(current_pdu->N_AI.N_TAtype == phyiscal){
			current_DataLinkParameter->Identifier = (current_pdu->N_AI.N_SA
			|=((unsigned long)current_pdu->N_AI.N_TA) << 8
			|=((unsigned long)0xCD<<16)
			|=((unsigned long)0x18<<24)
					);
		}
		else if(current_pdu->N_AI.N_TAtype == functional){
			current_DataLinkParameter->Identifier = (current_pdu->N_AI.N_SA
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
		current_DataLinkParameter->Data[0] = current_pdu->N_AI.N_AE;
		switch (current_pdu->N_PCI.PCIType){
		case SF:
			current_DataLinkParameter->Data[1] = current_pdu->N_PCI.PCI.BYTE.byte1;
			for(i = 2; i < 8; i++)
				current_DataLinkParameter->Data[i] = current_pdu->N_DATA.Nml_SF_Data[i-2];
			break;
		case FF:
			current_DataLinkParameter->Data[1] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->Data[2] = current_pdu->N_PCI.PCI.BYTE.byte2;
			for(i = 3; i < 8; i++)
				current_DataLinkParameter->Data[i] = current_pdu->N_DATA.Nml_SF_Data[i-3];
			break;
		case CF:
			current_DataLinkParameter->Data[1] = current_pdu->N_PCI.PCI.BYTE.byte1;
			for(i = 2; i < 8; i++)
				current_DataLinkParameter->Data[i] = current_pdu->N_DATA.Nml_SF_Data[i-2];
			break;
		case FC:
			current_DataLinkParameter->Data[1] = current_pdu->N_PCI.PCI.BYTE.byte1;
			current_DataLinkParameter->Data[2] = current_pdu->N_PCI.PCI.BYTE.byte2;
			current_DataLinkParameter->Data[3] = current_pdu->N_PCI.PCI.BYTE.byte3;
			for(i = 4; i < 8; i++)
				current_DataLinkParameter->Data[i] = current_pdu->N_DATA.Nml_SF_Data[i-4];
			break;
		}
		break;
	default:
		break;






	return current_DataReq;
}
/*
 * Function:
 * Description: SDU to PDUs
 * Input Parameter:
 * Output Parameter:
 * Return:
 *
 */
void N_SDU2N_PDUs(
		N_SDU_DataReq_type * current_sdu,
		N_PDU_type * n_pdu_output
		)
{
	if(current_sdu->Mtype == diagnostics){

	}
	else if(current_sdu->Mtype == remote_diagnostics)
	{

	}
}



/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void SenderCtrl_Init()
{
	CurData.Length = 1;
}


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void SenderCtrl_Reset()
{

}


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void SenderCtrl_Task()
{
	N_PDU_type current_pdu;
	unsigned short i;
	Transfer_Status_type transferStatus = Not_Complete;

	if(Sender.senderEnable == senderDisable)
		return;
	if()//if single frame
	{
		//
		//
		L_Data_Request();

	}
	else
	switch(Sender.senderState)
	{
	case sendFirstFrame:
		//
		//1.start request
		L_Data_Request();//FF N_PDU
		//2.star N_As timeout

		break;
	case waitSendFirstFrameSuccess:
		if()//N_As is timeout
		{
			break;
		}
		else if(getSendState()==SendSuccess)//N_As is not timeout, send success
		{
			L_Data_Confirm(1,transferStatus);
			SenderState_type = waitFlowCtrlFrame;
		}
		else//N_As is not timeout, send success
		{
			//just wait
		}
		break;
	case waitFlowCtrlFrame:
		//wait until(stateOfCAN == SuccessReceive , N_Bs )
		if()//no timeout
		{
			L_Data_Indication();//FF N_PDU
			SenderState_type = sendConsecutiveFrame;
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
				SenderState_type = waitFlowCtrlFrame;
			}
			else
			{
				L_Data_Confirm(1,Not_Complete);//1 = ID
				SenderState_type = finishFlow;
			}
		}
		SenderState_type = finishFlow;
		break;
	case finishFlow:

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
void N_USDataRequest(
		N_SDU_DataReq_type parameter){
	senderCtrl_Init();

}


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_USDataConfirm(
		N_SDU_DataCfm_type parameter){

}


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_USDataFFIndication(
		N_SDU_DataFFInd_type parameter){

}



/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_USDataIndication(
		N_SDU_DataInd_type parameter){

}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_ChangeParameterRequest(
		N_SDU_DataFFReq_type parameter){

}


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void N_ChangePatameterConfirm(
		N_SDU_ChgParaCfm_type parameter){

}
