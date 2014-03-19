#include "Std_Types.h"
#include "misratypes.h"
#include "kernel.h"
#include "mem.h"
#include "CanIf.h"
#include "CanIf_Types.h"
#include "OBD_N_task.h"
#include "OBD_N_Cfg.h"


#pragma noregsave(Task)


//#define SessResCtrl(a)
#define OBD_N_TSK_STACK_SIZE           0x0400U
#define OBD_N_TSK_PRIORITY             5U

static void* pStackBase;
static ID OsIdMainMbfOBDNetSess;
static ID OsIdMainTskOBDNetSess;

Session_type session;
N_SDU_DataReq_type curReqData;
N_PDU_type  PDU_queue[32];


static sint32_t Diag_GetMsg(SessMessage_type *msg);


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
N_Result_type N_PDU2L_SDU(
		N_PDU_type Current_N_pdu,
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
	if(Current_N_pdu.N_AI.N_TAtype == functional)
	{
		L_SDU_output->Identifier.Ext_ID.OBD.PF = NOR_FIX_FUN_PF;
	}
	else if(Current_N_pdu.N_AI.N_TAtype == phyiscal)
	{
		L_SDU_output->Identifier.Ext_ID.OBD.PF = NOR_FIX_PHY_PF;
	}
	else
	{}
	L_SDU_output->Identifier.Ext_ID.OBD.PS = Current_N_pdu.N_AI.N_TA;
	L_SDU_output->Identifier.Ext_ID.OBD.SA = Current_N_pdu.N_AI.N_SA;
	//2. Set DLC
	L_SDU_output->DLC = 8;
	//3. Set Data
	switch (Current_N_pdu.N_PCI.N_PCItype){
	case SF:
		L_SDU_output->Data[0] = Current_N_pdu.N_PCI.PCI.SF_PCI.BIT.SF_DL;
		for(i = 1; i < 8; i++)
			L_SDU_output->Data[i] = Current_N_pdu.N_DATA.Nml_SF_Data[i-1];
		break;
	case FF:
		L_SDU_output->Data[0] = (Current_N_pdu.N_PCI.N_PCItype
								||Current_N_pdu.N_PCI.PCI.Nybbles.Nybble1);
		L_SDU_output->Data[1] |= Current_N_pdu.N_PCI.PCI.FF_PCI.BIT.FF_DL;
		for(i = 2; i < 8; i++)
			L_SDU_output->Data[i] = Current_N_pdu.N_DATA.Nml_SF_Data[i-2];
		break;
	case CF:
		L_SDU_output->Data[0] |= Current_N_pdu.N_PCI.PCI.CF_PCI.BIT.SN;
		for(i = 1; i < 8; i++)
			L_SDU_output->Data[i] = Current_N_pdu.N_DATA.Nml_SF_Data[i-1];
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
N_PDU_type getN_PDUfromN_SDU(
		Request_type  current_request
		)
{
	N_PDU_type N_pdu_output;
	unsigned long i;

	//1. set N_AI
	N_pdu_output.N_AI.N_AE = current_request.ReqTxData.N_AI.N_AE;
	N_pdu_output.N_AI.N_SA = current_request.ReqTxData.N_AI.N_SA;
	N_pdu_output.N_AI.N_TA = current_request.ReqTxData.N_AI.N_TA;
	N_pdu_output.N_AI.N_TAtype = current_request.ReqTxData.N_AI.N_TAtype;
	if(current_request.ReqState == SF_req)
	{
		//2. set N_PCI
		N_pdu_output.N_PCI.N_PCItype = SF;
		N_pdu_output.N_PCI.PCI.SF_PCI.BIT.SF_DL = current_request.ReqTxData.Length;
		//3. set data
		for(i = 0; i < N_pdu_output.N_PCI.PCI.SF_PCI.BIT.SF_DL;
				i++,current_request.ReqTxedDataMark)
		{
			N_pdu_output.N_DATA.NF_SF_Data[i] =
				*(current_request.ReqTxData.MessageData + current_request.ReqTxedDataMark);
		}
	}
	else if(current_request.ReqState == FF_req)
	{
		//2. set N_PCI
		N_pdu_output.N_PCI.N_PCItype = FF;
		N_pdu_output.N_PCI.PCI.FF_PCI.BIT.FF_DL = current_request.ReqTxData.Length;

	}
	else if(current_request.ReqState == CF_req)
	{
		//2. set N_PCI
		N_pdu_output.N_PCI.N_PCItype = CF;
		N_pdu_output.N_PCI.PCI.CF_PCI.BIT.SN = current_request.sequenceNumber + 1;
		//3. set data
		for(i = 0;
				i < (current_request.ReqTxData.Length - session.request.ReqTxedDataMark < 7)?
				(current_request.ReqTxData.Length - session.request.ReqTxedDataMark):7;
				i++,current_request.ReqTxedDataMark++)
		{
			N_pdu_output.N_DATA.NF_CF_Data[i] =
					*(current_request.ReqTxData.MessageData + session.request.ReqTxedDataMark);
		}
	}
	else
	{

	}
	return N_pdu_output;

}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
N_Result_type InitSession()
{
	unsigned long i;
	N_Result_type result;
	result = N_ERROR;
	session.parameter.BS = default_BS;
	session.parameter.STmin = defaylt_STmin;

	session.request.ReqEnableState = reqEnable;
	session.request.ReqErrorState = N_OK;
	session.request.ReqState = req_ready;
	session.request.ReqTxedDataMark = 0;
	session.request.sequenceNumber = 0;
	session.request.ReqTxData.Length = 0;
	session.request.ReqTxData.N_AI.N_AE = 0x0;
	session.request.ReqTxData.N_AI.N_SA = 0x0;
	session.request.ReqTxData.N_AI.N_TA = 0x0;
	session.request.ReqTxData.N_AI.N_TAtype = functional;

	session.response.ResErrorState = N_OK;
	session.response.ResFlowstate  = ContinueToSend;
	session.response.ResRxedDataCounter = 0;
	session.response.ResState = res_reset;

	session.SessRunningMark = running;
	return result;
}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
N_Result_type ResetSession()
{
	unsigned long i;
	N_Result_type result;
	result = N_ERROR;
	session.parameter.BS = default_BS;
	session.parameter.STmin = defaylt_STmin;

	session.request.ReqEnableState = reqEnable;
	session.request.ReqErrorState = N_OK;
	session.request.ReqState = req_ready;
	session.request.ReqTxedDataMark = 0;
	session.request.sequenceNumber = 0;
	session.request.ReqTxData.Length = 0;
	session.request.ReqTxData.N_AI.N_AE = 0x0;
	session.request.ReqTxData.N_AI.N_SA = 0x0;
	session.request.ReqTxData.N_AI.N_TA = 0x0;
	session.request.ReqTxData.N_AI.N_TAtype = functional;

	session.response.ResErrorState = N_OK;
	session.response.ResFlowstate  = ContinueToSend;
	session.response.ResRxedDataCounter = 0;
	session.response.ResState = res_reset;

	session.SessRunningMark = running;
	return result;
}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
#pragma inline (ReqState_get)
static Request_type ReqState_get()
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
#pragma inline (ResState_get)
static Response_type ResState_get(uint16 index)
{
	return session.response[index];
}

/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
#pragma inline (FCFrame_generate)
static N_PDU_type FCFrame_generate(unsigned short ResponseIndex)
{
	N_PDU_type FC_Frame;

	FC_Frame.N_AI.N_SA = session.request.ReqTxData.N_AI.N_SA;
	FC_Frame.N_AI.N_TA = session.request.ReqTxData.N_AI.N_TA;
	FC_Frame.N_AI.N_TAtype = session.request.ReqTxData.N_AI.N_TAtype;

	FC_Frame.N_PCI.PCI.FC_PCI.BIT.BS = session.parameter.BS;
	FC_Frame.N_PCI.PCI.FC_PCI.BIT.STmin = session.parameter.STmin;

	FC_Frame.N_PCI.PCI.FC_PCI.BIT.FS = session.response[ResponseIndex].ResFlowstate;

	return FC_Frame;
}


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void ReqCtrl_Reset()
{

}


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
N_Result_type RequestCtrl(SessMessage_type currentN_PDU)
{
	unsigned short i,currnetSenderNO = 0;
	N_Result_type result;
	Transfer_Status_type transferStatus;
	L_SDU_DataReq_type currentL_SDU;

	result = N_ERROR;
	transferStatus = Not_Complete;
	if(session.request.ReqEnableState == reqDisable)
		return N_ERROR;

	switch(session.request.ReqState)
	{
	case SF_req:
		N_PDU2L_SDU(currentN_PDU.pdu_msg,&currentL_SDU);
		L_Data_Request(currentL_SDU);
		session.request.ReqState = req_ready;
		result = N_OK;
		break;
//	case FF_req:
//		if(session.request.ReqTxData.Length < MaxLenthOfSDUData)
//		{
//			//1.get a N_PDU from N_SDU
//			getN_PDUfromN_SDU(session.request,&currentN_PDU);
//			//2.N_PDU to L_SDU
//			currentL_SDU = N_PDU2L_SDU(&currentN_PDU,currentL_SDU);
//			//3.start request
//			L_Data_Request(currentL_SDU);
//			//4.star N_As timeout
//			//5.update sender state and TxedDataMark
//			session.request.ReqState = FF_con;
//		}
//		else
//		{}
//		break;
//	case FF_con:
//		if(0)//N_As is timeout
//		{
//			if(session.request.ReqErrorState != N_OK)
//				session.request.ReqErrorState = N_TIMEOUT_A;
//			break;
//		}
//		else if(session.request.ReqErrorState == N_OK)//N_As is not timeout, send success
//		{
//			L_Data_Confirm(1,transferStatus);
//			session.request.ReqState = waitFlowCtrlFrame;
//		}
//		else//N_As is not timeout, send success
//		{
//			//just wait
//		}
//		break;
//	case FC_ind:
//		//wait until(stateOfCAN == SuccessReceive , N_Bs )
//		if()//no timeout
//		{
//			L_Data_Indication();//FF N_PDU
//			session.request.ReqState = ReqConsecutiveFrame;
//		}
//		else
//		{
//		}
//		break;
//	case CF_req:
//		for(i = 0 ; i < 1 ; i++)//1 = BS
//		{
//			L_Data_Request();//FC N_PDU
//			//wait until(stateOfCAN == SuccessSend , N_As )
//			if()//no timeout
//			{
//				L_Data_Confirm(1,Complete);//1 = ID
//				session.request.ReqState = waitFlowCtrlFrame;
//			}
//			else
//			{
//				L_Data_Confirm(1,Not_Complete);//1 = ID
//				session.request.ReqState = finishFlow;
//			}
//		}
//		break;
//	case CF_con:
//
//		break;
//	case req_ready:
//		break;
	default:
		break;
	}

	return result;

}


N_Result_type ResponseCtrl(SessMessage_type currentN_PDU)
{
	unsigned short i,j;
	N_Result_type result;
	N_PDU_type FC_N_pdu;
	L_SDU_DataReq_type FC_L_sdu;

	result = N_ERROR;


	for(i = 0; i < ReponseMaxNumber;i++){
		if(currentN_PDU.pdu_msg.N_AI.N_TA != session.request.ReqTxData.N_AI.N_SA)
			break;

		switch(session.response[i].ResState){
		case FF_ind:
			//FF_indication
			session.response[i].ResRxData.N_AI = currentN_PDU.pdu_msg.N_AI;
			session.response[i].ResRxData.Length = currentN_PDU.pdu_msg.N_PCI.PCI.FF_PCI.BIT.FF_DL;
			for(j = 0 ;j < 6; j++)
			{
				*(session.response[i].ResRxData.MessageData + session.response[i].ResRxedDataCounter)
						= currentN_PDU.pdu_msg.N_DATA.NF_FF_Data[j];
				session.response[i].ResRxedDataCounter ++;
			}
			//FC_request
			FC_N_pdu = FCFrame_generate(i);
			N_PDU2L_SDU(FC_N_pdu,&FC_L_sdu);
			session.response[i].ResState = FC_con;
			break;
		case FC_con:
			session.response[i].ResState = CF_ind;
				break;
		case CF_ind:

			for(j = 0 ;j < 7; j++,session.response[i].ResRxedDataCounter++)
			{
				if(session.response[i].ResRxedDataCounter
						>= session.response[i].ResRxData.Length)
					break;
				*(session.response[i].ResRxData.MessageData + session.response[i].ResRxedDataCounter)
						= currentN_PDU.pdu_msg.N_DATA.NF_FF_Data[j];
			}
			if(session.response[i].ResRxedDataCounter % session.parameter.BS == 0
					&& session.response[i].ResRxedDataCounter < session.response[i].ResRxData.Length)
			{
				FC_N_pdu = FCFrame_generate(i);
				N_PDU2L_SDU(FC_N_pdu,&FC_L_sdu);
			}
			break;
		case res_reset:
				break;
		}
	}
	return result;
}


/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
N_Result_type N_USDataRequest(
		N_SDU_DataReq_type parameter){
	N_Result_type result;
	N_PDU_type current_pdu;
	result = N_ERROR;

	session.SessRunningMark = running;
	session.request.ReqTxData = parameter;

	if(parameter.Mtype == diagnostics && parameter.Length <= 7)
		session.request.ReqState = SF_req;
	else
		session.request.ReqState = FF_req;
	current_pdu = getN_PDUfromN_SDU(session.request);
	result = snd_mbf(OsIdMainMbfOBDNetSess, &current_pdu, sizeof(current_pdu));
	return result;
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
static sint32_t Diag_GetMsg(SessMessage_type *msg)
{
	ER_UINT msgsz;
	SessMessage_type msgbuf;

	msgsz = rcv_mbf(OsIdMainTskOBDNetSess,&msgbuf);

	switch(msgsz)
	{
	case E_PAR:
	case E_ID:
	case E_NOEXS:
	case E_CTX:
	case E_DLT:
	case E_TMOUT:
	case E_RLWAI:
		return -1;
		break;
	default:
		*msg = msgbuf;
		break;
	}

	return 0;

}



/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */
void OBD_Sess_Task(VP_INT exinf)
{
/* task processing */
	uint16 i;
	static SessMessage_type sess_msg;
	static SessMassageState sessState;

	for(;;)
	{
		Diag_GetMsg(&sess_msg);
		switch (sessState)
		{
		case sess_request:
			RequestCtrl(sess_msg);
			if(ReqState_get().ReqState == req_complete)
				sessState = sess_response;
			break;
		case sess_response:
			ResponseCtrl(sess_msg);
			for(i = 0; i < ReponseMaxNumber; i++)
			{
				if(ResState_get(i).ResState == res_reset)
				{


				}
			}
			break;
		}
	}


	ext_tsk( );
}




/*
 * Function:
 * Description:
 * Parameter:
 * Return:
 *
 */



OBDSessTsk_ReturnType OBD_Task_Init(void)
{
	T_CTSK CreateTsk;
	T_CMBF CreateMbf;
	ER ErrCode = E_OK;

	/* create can auto baudrate detection task */
	CreateTsk.tskatr = TA_HLNG | TA_COP1;
	CreateTsk.exinf = (VP_INT) NULL;
	CreateTsk.task = (FP) OBD_Sess_Task;
	CreateTsk.itskpri = OBD_N_TSK_PRIORITY;
	CreateTsk.stksz = OBD_N_TSK_STACK_SIZE;
	pStackBase = Mem_Allocate(OBD_N_TSK_STACK_SIZE, FALSE, TRUE);
	CreateTsk.stk = pStackBase;
	ErrCode = acre_tsk(&CreateTsk);
	if (ErrCode <= 0U) {
		Mem_Free(pStackBase);
		return OBD_SESS_ERR_OS_CFG;
	}
	else {
		OsIdMainTskOBDNetSess = (ID) ErrCode;
	}

	/* Message buffer for auto baudrate detection */
	CreateMbf.mbfatr = TA_TFIFO;
	CreateMbf.maxmsz = 12u;
	CreateMbf.mbfsz = 0x100;
	ErrCode = acre_mbf(&CreateMbf);
	if (ErrCode > 0U) {
		OsIdMainMbfOBDNetSess = (ID) ErrCode;
		InitSession();
	}
	else {
		OsIdMainMbfOBDNetSess = 0U;
		del_tsk(OsIdMainTskOBDNetSess);
		return (OBDSessTsk_ReturnType)OBD_SESS_ERR_OS_CFG;
	}
	/* start task */
	sta_tsk(OsIdMainTskOBDNetSess, 0);
	return (OBDSessTsk_ReturnType)OBD_SESS_TSK_ERR_OK;
}
