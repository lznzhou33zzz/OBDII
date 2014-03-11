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

Session_type session;
N_SDU_DataReq_type curReqData;
N_PDU_type  PDU_queue[32];




/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
N_Result_type N_PDU2L_SDU(
		N_PDU_type * Current_N_pdu,
		L_SDU_DataReq_type *L_SDU_output)
{
	N_Result_type result;
	short i;
//	if(current_sender->senderTxData->Mtype == diagnostics)
//	{
//
//	}
//	else if(current_sender->senderTxData->Mtype == remote_diagnostics)
//	{
//
//	}

	//1. Set ID
	//	 this function should be replenished
	L_SDU_output->Identifier.Ext_ID.OBD.P = default_P;
	L_SDU_output->Identifier.Ext_ID.OBD.R = default_R;
	L_SDU_output->Identifier.Ext_ID.OBD.DP = default_DP;
	if(Current_N_pdu->N_AI.N_TAtype == functional)
	{
		L_SDU_output->Identifier.Ext_ID.OBD.PF = NOR_FIX_FUN_PF;
	}
	else if(Current_N_pdu->N_AI.N_TAtype == phyiscal)
	{
		L_SDU_output->Identifier.Ext_ID.OBD.PF = NOR_FIX_PHY_PF;
	}
	else
	{}
	L_SDU_output->Identifier.Ext_ID.OBD.PS = Current_N_pdu->N_AI.N_TA;
	L_SDU_output->Identifier.Ext_ID.OBD.SA = Current_N_pdu->N_AI.N_SA;
	//2. Set DLC
	L_SDU_output.DLC = 8;
	//3. Set Data
	switch (Current_N_pdu->N_PCI.N_PCItype){
	case SF:
		L_SDU_output->Data[0] = Current_N_pdu->N_PCI.PCI.SF_PCI.BIT.SF_DL;
		for(i = 1; i < 8; i++)
			L_SDU_output->Data[i] = Current_N_pdu->N_DATA.Nml_SF_Data[i-1];
		break;
	case FF:
		L_SDU_output->Data[0] = (Current_N_pdu->N_PCI.N_PCItype
								||Current_N_pdu->N_PCI.PCI.Nybbles.Nybble1);
		L_SDU_output->Data[1] |= Current_N_pdu->N_PCI.PCI.FF_PCI.BIT.FF_DL;
		for(i = 2; i < 8; i++)
			L_SDU_output->Data[i] = Current_N_pdu->N_DATA.Nml_SF_Data[i-2];
		break;
	case CF:
		L_SDU_output->Data[0] |= Current_N_pdu->N_PCI.PCI.CF_PCI.BIT.SN;
		for(i = 1; i < 8; i++)
			L_SDU_output->Data[i] = Current_N_pdu->N_DATA.Nml_SF_Data[i-1];
		break;
//	case FC:
//		L_SDU_output->Data[0] = Current_N_pdu->N_PCI.PCI.;
//		L_SDU_output->Data[1] = Current_N_pdu->N_PCI.PCI.;
//		L_SDU_output->Data[2] = Current_N_pdu->N_PCI.PCI.;
//		for(i = 3; i < 8; i++)
//			L_SDU_output->Data[i] = Current_N_pdu->N_DATA.Nml_SF_Data[i-3];
//		break;
	default:
		break;
	}



	return result;
}

/*
 * Function:
 * Description: SDU to PDUs
 * Input Parameter:
 * Output Parameter:
 * Return:
 *
 */
N_Result_type getN_PDUfromN_SDU(
		Request_type * current_request,
		N_PDU_type * N_PDU_output
		)
{
	N_PDU_type N_pdu_output;
	unsigned long i;

	//1. set N_AI
	N_pdu_output.N_AI.N_AE = current_request->senderTxData.N_AI.N_AE;
	N_pdu_output.N_AI.N_SA = current_request->senderTxData.N_AI.N_SA;
	N_pdu_output.N_AI.N_TA = current_request->senderTxData.N_AI.N_TA;
	N_pdu_output.N_AI.N_TAtype = current_request->senderTxData.N_AI.N_TAtype;
	if(current_request->ReqState == SF_req)
	{
		//2. set N_PCI
		N_pdu_output.N_PCI.N_PCItype = SF;
		N_pdu_output.N_PCI.PCI.SF_PCI.BIT.SF_DL = current_request->senderTxData.Length;
		//3. set data
		for(i = 0; i < N_pdu_output.N_PCI.PCI.SF_PCI.BIT.SF_DL; i++,current_request->senderTxedDataMark)
		{
			N_pdu_output.N_DATA.NF_SF_Data[i] =
				*(current_request->senderTxData.MessageData + current_request->senderTxedDataMark);
		}
	}
	else if(current_request->ReqState == FF_req)
	{
		//2. set N_PCI
		N_pdu_output.N_PCI.N_PCItype = FF;
		N_pdu_output.N_PCI.PCI.FF_PCI.BIT.FF_DL = current_request->senderTxData.Length;

	}
	else if(current_request->ReqState == CF_req)
	{
		//2. set N_PCI
		N_pdu_output.N_PCI.N_PCItype = CF;
		N_pdu_output.N_PCI.PCI.CF_PCI.BIT.SN = current_request->sequenceNumber + 1;
		//3. set data
		for(i = 0;
				i < (current_request->senderTxData.Length - SenderTxedDataMark < 7)?
				(current_request->senderTxData.Length - SenderTxedDataMark):7; i++,current_request->senderTxedDataMark++)
		{
			N_pdu_output.N_DATA.NF_CF_Data[i] =
					*(current_request->senderTxData.MessageData + SenderTxedDataMark);
		}
	}
	else
	{

	}
		return N_ERROR;




	return N_OK;
}



/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
N_Result_type NewSession()
{
	unsigned long i;
	N_Result_type result;
	result = N_ERROR;
//	for(i = 0; i < SenderMaxNumber; i++)
//	{
//		if(Sender[i].senderEnablestate == senderEnable)
//			continue;
//		else
//		{
//			Sender[i].senderEnablestate = senderEnable;
//			// add other parameter init
//
//
//
//
//
//			result = N_OK;
//		}
//	}
	return result;
}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
inline Request_type ReqState_get()
{
	return session.request;
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
void RequestCtrl(N_SDU_Type currentN_SDU)
{
	unsigned short i,currnetSenderNO = 0;
	Transfer_Status_type transferStatus = Not_Complete;
	N_PDU_type currentN_PDU;
	L_SDU_DataReq_type currentL_SDU;


	if(session.request.ReqEnableState == senderDisable)
		return;

	switch(session.request.ReqState)
	{
	case SF_req:
		//1.get a N_PDU from N_SDU
		getN_PDUfromN_SDU(session.request,&currentN_PDU);
		currentL_SDU = N_PDU2L_SDU(&currentN_PDU,currentL_SDU);
		L_Data_Request(currentL_SDU);
		session.request.ReqState = req_reset;
		break;
	case FF_req:
		if(session.request.ReqTxData.Length < MaxLenthOfSDUData)
		{
			//1.get a N_PDU from N_SDU
			getN_PDUfromN_SDU(session.request,&currentN_PDU);
			//2.N_PDU to L_SDU
			currentL_SDU = N_PDU2L_SDU(&currentN_PDU,currentL_SDU);
			//3.start request
			L_Data_Request(currentL_SDU);
			//4.star N_As timeout
			//5.update sender state and TxedDataMark
			session.request.ReqState = FF_con;
		}
		else
		{}
		break;
	case FF_con:
		if(0)//N_As is timeout
		{
			if(session.request.ReqErrorState != N_OK)
				session.request.ReqErrorState = N_TIMEOUT_A;
			break;
		}
		else if(session.request.ReqErrorState == N_OK)//N_As is not timeout, send success
		{
			L_Data_Confirm(1,transferStatus);
			session.request.ReqState = waitFlowCtrlFrame;
		}
		else//N_As is not timeout, send success
		{
			//just wait
		}
		break;
	case FC_ind:
		//wait until(stateOfCAN == SuccessReceive , N_Bs )
		if()//no timeout
		{
			L_Data_Indication();//FF N_PDU
			session.request.ReqState = ReqConsecutiveFrame;
		}
		else
		{
		}
		break;
	case CF_req:
		for(i = 0 ; i < 1 ; i++)//1 = BS
		{
			L_Data_Request();//FC N_PDU
			//wait until(stateOfCAN == SuccessSend , N_As )
			if()//no timeout
			{
				L_Data_Confirm(1,Complete);//1 = ID
				session.request.ReqState = waitFlowCtrlFrame;
			}
			else
			{
				L_Data_Confirm(1,Not_Complete);//1 = ID
				session.request.ReqState = finishFlow;
			}
		}
		break;
	case CF_con:

		break;
	case req_reset:
		break;
	default:
		break;
	}



}


void ResponseCtrl(N_SDU_Type currentN_SDU)
{
	switch(session.response.ResState){
	case FF_ind:
		break;
	case FC_req:
			break;
	case FC_con:
			break;
	case CF_ind:
			break;
	case res_reset:
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
	NewSender();

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
