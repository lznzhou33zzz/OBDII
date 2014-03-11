#include <machine.h>
#include "Std_Types.h"
#include "misratypes.h"
#include "kernel.h"
#include "mem.h"
#include "Session_Type.h"
#include "Common.h"
#include "Network.h"

#pragma noregsave(Task)

#define CAN_TSK_STACK_SIZE           0x0400U
#define CAN_TSK_PRIORITY             5U


static ID OsIdMainTskDiag;
static ID OsIdMainMbfDiag;

static sint32_t Diag_GetMsg(N_SDU_Type *msg);


void Diag_Sess_Task(VP_INT exinf)
{
/* task processing */
	static N_SDU_Type sess_msg;
	static SessMassageState sessState;
	NewSender();

	for(;;)
	{
		Diag_GetMsg(sess_msg);
		switch (sessState)
		{
		case sess_request:
			RequestCtrl(sess_msg);
			if(ReqState_get().ReqState == req_reset)
				sessState = sess_response;
			break;
		case sess_response:
			ResponseCtrl(sess_msg);
			if(sender_get().ReqState == Sender_reset)
				sessState = sess_response;
			break;
		case sess_cbk:

			break;
		}
	}


	ext_tsk( );
}





static sint32_t Diag_GetMsg(SessMsgDataType *msg)
{
	ER_UINT msgsz;
	SessMsgDataType msgbuf;

	msgsz = rcv_mbf(OsIdMainTskDiag,msgbuf);

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


CANTsk_ReturnType CAN_Task_Init(void)
{
	T_CTSK CreateTsk;
	T_CMBF CreateMbf;
	ER ErrCode = E_OK;

	/* create can auto baudrate detection task */
	CreateTsk.tskatr = TA_HLNG | TA_COP1;
	CreateTsk.exinf = (VP_INT) NULL;
	CreateTsk.task = (FP) CAN_Task;
	CreateTsk.itskpri = CAN_TSK_PRIORITY;
	CreateTsk.stksz = CAN_TSK_STACK_SIZE;
	pStackBase = Mem_Allocate(CAN_TSK_STACK_SIZE, FALSE, TRUE);
	CreateTsk.stk = pStackBase;
	ErrCode = acre_tsk(&CreateTsk);
	if (ErrCode <= 0U) {
		Mem_Free(pStackBase);
		return CANTSK_ERR_OS_CFG;
	}
	else {
		OsIdMainTskCan = (ID) ErrCode;
	}

	/* Message buffer for auto baudrate detection */
	CreateMbf.mbfatr = TA_TFIFO;
	CreateMbf.maxmsz = 12u;
	CreateMbf.mbfsz = 0x100;
	ErrCode = acre_mbf(&CreateMbf);
	if (ErrCode > 0U) {
		OsIdMainMbfCan = (ID) ErrCode;
	}
	else {
		OsIdMainMbfCan = 0U;
		del_tsk(OsIdMainTskCan);
		return -1;
	}

	/* start task */
	sta_tsk(OsIdMainTskCan, 0);
}
