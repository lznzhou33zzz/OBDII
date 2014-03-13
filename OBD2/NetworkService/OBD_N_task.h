/*
 * OBD_N_task.h
 *
 *  Created on: 2014Äê3ÔÂ9ÈÕ
 *      Author: zezhongzhao
 */

#ifndef OBD_N_TASK_H_
#define OBD_N_TASK_H_

#include "Network_Type.h"
#include "Common.h"

#define N_FWTmax
#define TIMEOUT_N_As			1000
#define TIMEOUT_N_Ar			1000
#define TIMEOUT_B_Bs			1000
#define TIMEOUT_N_Cr			1000


//Error about
#define NetLayerErrorType		unsigned short
#define NE_OK					0
#define NE_OVERTIME				1



static ID OsIdMainMbfOBDNetSess;

#endif /* OBD_N_TASK_H_ */
