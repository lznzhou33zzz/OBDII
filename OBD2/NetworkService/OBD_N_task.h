/*
/*
 * OBD_N_task.h
 *
 *  Created on: 2014年3月9日
 *      Author: zezhongzhao
 */

#ifndef OBD_N_TASK_H_
#define OBD_N_TASK_H_
#include "OBD_N_Cfg.h"
#include "Std_Types.h"
#define N_FWTmax



//Error about
#define NetLayerErrorType		unsigned short
#define NE_OK					0
#define NE_OVERTIME				1

//task about
#define OBD_SESS_TSK_ERR_OK                  0
#define OBD_SESS_ERR_OS_CFG              (-1)
#define OBD_SESS_ERR_PARA                (-2)


//------DATA type------//

typedef sint32 OBDSessTsk_ReturnType;

typedef enum{
	ContinueToSend,
	Wait,
	Overflow
}FS_type;

typedef enum {
	req_ready,
	SF_req,
	FF_req,
	FF_con,
	FC_ind,
	CF_req,
	CF_con,
	req_complete
}ReqState_type;

typedef enum{
	reqEnable ,
	reqDisable
}ReqEnable_type;

typedef unsigned long ReqTxedDataMark;
typedef unsigned char SequenceNumber;

typedef enum {
	FF_ind,
	FC_con,
	CF_ind,
	res_reset
}ResponseState_type;

typedef enum{
	ResponseEnable ,
	ResponseDisable
}ResponseEnable_type;
typedef unsigned long ResponseRxedDataCounter;

typedef enum{
	running,
	stoped
}SessRunningMark_type;

typedef struct{
	unsigned char BS;
	unsigned char STmin;
}SessionParameter_type;




typedef enum {
	SF,
	FF,
	CF,
	FC
}PCIType_type;

typedef enum {
	normal_address,
	normal_fixed_address,
	extended_address,
	mixed_address
}Exchange_address_type;
typedef enum {
	diagnostics,
	remote_diagnostics
}Message_type;
typedef enum {
	phyiscal,
	functional
}Address_type;
typedef enum {
	STmin,
	BS
}Parameter_type;
typedef enum {
	N_OK,
	N_TIMEOUT_A,
	N_TIMEOUT_Bs,
	N_TIMEOUT_Cr,
	N_WRONG_SN,
	N_INVALID_FS,
	N_UNEXP_PDU,
	N_WFT_OVRN,
	N_BUFFER_OVFLW,
	N_ERROR
}N_Result_type;

typedef enum {
	ParaN_OK,
	ParaN_RX_ON,
	ParaN_WRONG_PARAMETER,
	ParaN_WRONG_VALUE
}Result_ChangeParameter_type;




/*-------------------------------protocol data unit-------------------------------*/
	typedef struct{
		unsigned char N_SA;
		unsigned char N_TA;
		Address_type N_TAtype;		//network address type
		unsigned char N_AE;			//network address extension
	}N_AI_type;
	typedef struct{
		unsigned char N_PCItype:4;
		union{
			struct{
				struct{
					unsigned char SF_DL:4;
				}BIT;
			}SF_PCI;//SingleFrame
			struct{
				struct{
					unsigned short FF_DL:12;
				}BIT;
			}FF_PCI;//FirstFrame
			struct{
				struct{
					unsigned char SN :4;
				}BIT;
			}CF_PCI;//ConsecutiveFrame
			struct{
				struct{
					FS_type FS:4;
					unsigned char BS;
					unsigned char STmin;
				}BIT;
			}FC_PCI;//FlowControl
			struct {
				unsigned char Nybble1:4;
				unsigned char Nybble23;
				unsigned char Nybble45;
			}Nybbles;
		}PCI;
	}N_PCI_type;
	typedef union{
		//normal addressing
		unsigned char Nml_SF_Data[7];//SingleFrame
		unsigned char Nml_FF_Data[6];//FirstFrame
		unsigned char Nml_CF_Data[7];//ConsecutiveFrame

		//Normal fixed addressing
		unsigned char NF_SF_Data[7];//SingleFrame
		unsigned char NF_FF_Data[6];//FirstFrame
		unsigned char NF_CF_Data[7];//ConsecutiveFrame

		//Extended addressing
		unsigned char Ext_SF_Data[6];//SingleFrame
		unsigned char Ext_FF_Data[5];//FirstFrame
		unsigned char Ext_CF_Data[6];//ConsecutiveFrame

		//Mixed addressing
		unsigned char Mix_SF_Data[7];//SingleFrame
		unsigned char Mix_FF_Data[6];//FirstFrame
		unsigned char Mix_CF_Data[7];//ConsecutiveFrame

	}N_DATA_type;
/*------------------- N_PDU ------------------*/
typedef struct {
	N_AI_type N_AI;
	N_PCI_type	N_PCI;
	N_DATA_type N_DATA;
}N_PDU_type;
/*----------------- N_PDU end-----------------*/

/*------------------------------protocol data unit end-------------------------*/



/*----------------------------Network layer service------------------------*/
/*-----------------N_USDATA------------------
 * request:这项基本服务请求传输带有“长度”字节的“信息
 * 		数据”，从发送器到接收器，同时通过在N_SA、N_TA、
 * 		N_TAtype、和N_AE中地址信息进行硬件认证。每次只要
 * 		N_USData.request发生了，网络层就要标识向服务用
 * 		户传输信息成功（或失败），通过看N_USData.confirm
 * 		这项服务是否被请求了。
 * confirm:此服务是网络层发出。基本的服务确定
 * 		N_USData.request是否已经完成，通过在N_SA、
 * 		N_TA、N_TAtype、和N_AE中地址信息进行认证。参数
 * 		<N_Result>提供服务请求的状态
 * indication:此服务也是由网络层发出。这项基本的服务
 * 		指示<N_Result>事件和传递来自一个对等的协议硬件的带
 * 		有“长度”字节的“信息数据”到相邻的上层，这些带有“长度”
 * 		字节的“信息数据”通过在N_SA、N_TA、N_TAtype、和
 * 		N_AE中地址信息进行认证,<MessageData>和<Length>
 * 		参数仅仅在<N_Result>等于N_OK的情况下有效
 * ------------------------------------------*/
/*---------request-----------*/
typedef struct{
	Message_type Mtype;
	N_AI_type N_AI;
	unsigned char *MessageData;
	unsigned short Length;
}N_SDU_DataReq_type;
/*--------request end---------*/

/*----------confirm-----------*/
typedef struct{
	Message_type Mtype;
	N_AI_type N_AI;
	N_Result_type N_Result;
}N_SDU_DataCfm_type;
/*--------confirm end---------*/
/*---------indication-----------*/
typedef struct{
	Message_type Mtype;
	N_AI_type N_AI;
	unsigned char *MessageData;
	unsigned short Length;
}N_SDU_DataInd_type;
/*--------indication end---------*/
/*------------N_USDATA end------------*/


/*--------------N_USDATA_FF---------------
 * indication:此服务由网络层发出。基本的服务表示相邻上
 * 		层接收到一个分段信息的第一帧，来自一个对等的协议硬件，通
 * 		过在N_SA、N_TA、N_TAtype、和N_AE中地址信息进行
 * 		认证
 * --------------------------------------*/
/*---------indication-----------*/
typedef struct{
	Message_type Mtype;
	N_AI_type N_AI;
	unsigned short Length;
}N_SDU_DataFFInd_type;
/*--------indication end---------*/
/*------------N_USDATA_FF end------------*/


/*--------------N_ChangeParameter---------------
 * request:此项服务是用来请求对局部协议硬件上的内部参数值进行修改。参
 *		此项服务是用来请求对局部协议硬件上的内部参数值进行修改。参数
 *		修改总是可能的，除了接收到（N_USData_FF.indication）
 *		的第一帧之后和直到接收到（N_USData.indication）的通信
 *		信息的结束
 * confirm:此项基本服务确认N_ChangeParameter.Confirmation
 * 		此项基本服务确认N_ChangeParameter.Confirmation服务
 * 		申请信息的完成，通过在N_SA、N_TA、N_TAtype、和N_AE中地址
 * 		信息进行认证
 * */
/*---------request-----------*/
typedef struct{
	Message_type Mtype;
	N_AI_type N_AI;
	Parameter_type Parameter;
	unsigned short Parameter_Value;
}N_SDU_DataFFReq_type;
/*--------request end---------*/
/*---------Confirm-----------*/
typedef struct{
	Message_type Mtype;
	N_AI_type N_AI;
	Parameter_type Parameter;
	Result_ChangeParameter_type Result_changeParameter;
}N_SDU_ChgParaCfm_type;
/*--------Confirm end---------*/
/*-------------N_ChangeParameter end------------*/
/*------------------Network layer service end------------------*/


typedef enum{
	DataReq,
	DataCfm,
	DataInd,
	DataFFInd,
	DataFFReq,
	ChgParaCfm
}SDUtype_Type;
typedef struct{
	union{
		N_SDU_DataReq_type 		DataReqMsg;
		N_SDU_DataCfm_type 		DataCfmMsg;
		N_SDU_DataInd_type 		DataIndMsg;
		N_SDU_DataFFInd_type 	DataFFIndMsg;
		N_SDU_DataFFReq_type 	DataFFReqMsg;
		N_SDU_ChgParaCfm_type 	ChgParaCfmMsg;
	}SDUdata;
	SDUtype_Type SDUtype;
}N_SDU_Type;

typedef enum {
	sess_request,
	sess_response
}SessMassageState;

typedef union{
	N_SDU_Type sdu_msg;
	N_PDU_type pdu_msg;
}SessMessage_type;


typedef struct{
	ReqState_type	ReqState;
	ReqEnable_type	ReqEnableState;
	ReqTxedDataMark 	ReqTxedDataMark;//the index number of MessageData
	SequenceNumber		sequenceNumber;
	N_SDU_DataReq_type	ReqTxData;
	N_Result_type		ReqErrorState;
}Request_type;


typedef struct{
	FS_type					ResFlowstate;
	ResponseState_type		ResState;
	ResponseEnable_type		ResEnableState;
	ResponseRxedDataCounter 	ResRxedDataCounter;//the index number of MessageData
	N_SDU_DataInd_type		ResRxData;
	N_Result_type			ResErrorState;
}Response_type;

typedef struct{
	SessionParameter_type parameter;
	Request_type request;
	Response_type response[ReponseMaxNumber];
	SessRunningMark_type SessRunningMark;
}Session_type;

#endif /* OBD_N_TASK_H_ */
