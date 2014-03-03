/*
 * OBDII.c
 *
 *  Created on: 2013Äê10ÔÂ2ÈÕ
 *      Author: zezhongzhao
 */

char *
dtc_decode(uint8 *data, uint32 len, uint8 *vehicle, uint8 *ecu, uint32 protocol)
{
	static char buf[1024];
	char area;


		switch ((data[0] >> 6) & 0x03)	/* Top 2 bits are area */
		{
		case 0:
			area = 'P';
			break;
		case 1:
			area = 'C';
			break;
		case 2:
			area = 'B';
			break;
		case 3:
			area = 'U';
			break;
		}
		break;

	return(buf);
}
#include <machine.h>
#include "Std_Types.h"
#include "misratypes.h"
#include "kernel.h"
#include "mem.h"
#pragma noregsave(Task)

#define CAN_TSK_STACK_SIZE           0x0400U
#define CAN_TSK_PRIORITY             5U


static ID OsIdMainTskCan;
static ID OsIdMainMbfCan;




void Task(VP_INT exinf)
{
/* task processing */
	rcv_mbf(ID mbfid, VP msg);
	for(;;)
	{
		switch (msg)
		{
		case msg(value);
			break;
		}
	}


	ext_tsk( );
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
