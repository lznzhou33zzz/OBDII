/*
 * NetworkType.h
 *
 *  Created on: 2014��1��10��
 *      Author: zezhongzhao
 */

#ifndef NETWORK_TYPE_H_
#define NETWORK_TYPE_H_

enum {
	idle,
	sendFirstFrame,
	waitSendFirstFrameSuccess,
	waitFlowCtrlFrame,
	sendConsecutiveFrame,
	finishFlow,
}NetworkLayerFlowState;

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
	N_OK,
	N_RX_ON,
	N_WRONG_PARAMETER,
	N_WRONG_VALUE
}Result_ChangeParameter_type;

typedef enum{
	ContinueToSend,
	Wait,
	Overflow
}FS_type;


/*------------------������������淶-----------------*/
	/*-----------------N_USDATA------------------
	 * request:�������������������С����ȡ��ֽڵġ���Ϣ
	 * 		���ݡ����ӷ���������������ͬʱͨ����N_SA��N_TA��
	 * 		N_TAtype����N_AE�е�ַ��Ϣ����Ӳ����֤��ÿ��ֻҪ
	 * 		N_USData.request�����ˣ�������Ҫ��ʶ�������
	 * 		��������Ϣ�ɹ�����ʧ�ܣ���ͨ����N_USData.confirm
	 * 		��������Ƿ������ˡ�
	 * confirm:�˷���������㷢���������ķ���ȷ��
	 * 		N_USData.request�Ƿ��Ѿ���ɣ�ͨ����N_SA��
	 * 		N_TA��N_TAtype����N_AE�е�ַ��Ϣ������֤������
	 * 		<N_Result>�ṩ���������״̬
	 * indication:�˷���Ҳ��������㷢������������ķ���
	 * 		ָʾ<N_Result>�¼��ʹ�������һ���Եȵ�Э��Ӳ���Ĵ�
	 * 		�С����ȡ��ֽڵġ���Ϣ���ݡ������ڵ��ϲ㣬��Щ���С����ȡ�
	 * 		�ֽڵġ���Ϣ���ݡ�ͨ����N_SA��N_TA��N_TAtype����
	 * 		N_AE�е�ַ��Ϣ������֤,<MessageData>��<Length>
	 * 		����������<N_Result>����N_OK���������Ч
	 * ------------------------------------------*/
	/*---------request-----------*/
	typedef struct{
		Message_type Mtype;
		unsigned char N_SA;
		unsigned char N_TA;
		Address_type N_TAtype;		//network address type
		unsigned char N_AE;			//network address extension
		unsigned char *MessageData;
		unsigned short Length;
	}DATA_Request_type;
	/*--------request end---------*/

	/*----------confirm-----------*/
	typedef struct{
		Message_type Mtype;
		unsigned char N_SA;
		unsigned char N_TA;
		Address_type N_TAtype;
		unsigned char N_AE;
		N_Result_type N_Result;
	}DATA_Confirm_type;
	/*--------confirm end---------*/
	/*---------indication-----------*/
	typedef struct{
		Message_type Mtype;
		unsigned char N_SA;
		unsigned char N_TA;
		Address_type N_TAtype;		//network address type
		unsigned char N_AE;			//network address extension
		unsigned char *MessageData;
		unsigned short Length;
	}DATA_Indication_type;
	/*--------indication end---------*/
	typedef struct{
		DATA_Request_type request;
		DATA_Confirm_type confirm;
	}N_USData_type;
	/*------------N_USDATA end------------*/


	/*--------------N_USDATA_FF---------------
	 * indication:�˷���������㷢���������ķ����ʾ������
	 * 		����յ�һ���ֶ���Ϣ�ĵ�һ֡������һ���Եȵ�Э��Ӳ����ͨ
	 * 		����N_SA��N_TA��N_TAtype����N_AE�е�ַ��Ϣ����
	 * 		��֤									 									 *
	 * --------------------------------------*/

	/*---------indication-----------*/
	typedef struct{
		Message_type Mtype;
		unsigned char N_SA;
		unsigned char N_TA;
		Address_type N_TAtype;		//network address type
		unsigned char N_AE;			//network address extension
		unsigned short Length;
	}DATA_FF_Indication_type;
	/*--------indication end---------*/

	typedef struct{
		DATA_FF_Indication_type indication;
	}N_USDataFF_type;
	/*------------N_USDATA_FF end------------*/


	/*--------------N_ChangeParameter---------------
	 * request:�����������������Ծֲ�Э��Ӳ���ϵ��ڲ�����ֵ�����޸ġ���
	 *		�����������������Ծֲ�Э��Ӳ���ϵ��ڲ�����ֵ�����޸ġ�����
	 *		�޸����ǿ��ܵģ����˽��յ���N_USData_FF.indication��
	 *		�ĵ�һ֮֡���ֱ�����յ���N_USData.indication����ͨ��
	 *		��Ϣ�Ľ���
	 * confirm:�����������ȷ��N_ChangeParameter.Confirmation
	 * 		�����������ȷ��N_ChangeParameter.Confirmation����
	 * 		������Ϣ����ɣ�ͨ����N_SA��N_TA��N_TAtype����N_AE�е�ַ
	 * 		��Ϣ������֤
	 * */
	/*---------request-----------*/
	typedef struct{
		Message_type Mtype;
		unsigned char N_SA;
		unsigned char N_TA;
		Address_type N_TAtype;		//network address type
		unsigned char N_AE;			//network address extension
		Parameter_type Parameter;
		unsigned char Parameter_Value;
	}DATA_FF_Request_type;
	/*--------request end---------*/
	/*---------Confirm-----------*/
	typedef struct{
		Message_type Mtype;
		unsigned char N_SA;
		unsigned char N_TA;
		Address_type N_TAtype;		//network address type
		unsigned char N_AE;			//network address extension
		Parameter_type Parameter;
		Result_ChangeParameter_type Result_changeParameter;
	}Change_Para_Confirm_type;
	/*--------Confirm end---------*/

	typedef struct{
		DATA_FF_Request_type request;
		Change_Para_Confirm_type confirm;
	}N_USDataFF_type;
	/*-------------N_ChangeParameter end------------*/
/*------------------������������淶 end------------------*/


/*----------------------�����Э��--------------------*/
	typedef struct{
		Exchange_address_type AddressType;
		unsigned char N_SA;
		unsigned char N_TA;
		Address_type N_TAtype;		//network address type
		unsigned char N_AE;			//network address extension
	}N_AI_type;
	typedef struct{
		union{
			struct{
				struct{
					unsigned char N_PCItype:4 = SF;
					unsigned char SF_DL:4;
				}BIT;
			}SF_PCI;//SingleFrame
			struct{
				struct{
					unsigned char N_PCItype:4 = FF;
					unsigned short FF_DL:12;
				}BIT;
			}FF_PCI;//FirstFrame
			struct{
				struct{
					unsigned char N_PCItype = CF;
				}BIT;
			}CF_PCI;//ConsecutiveFrame
			struct{
				struct{
					unsigned char N_PCItype:4 = FC;
					FS_type FS:4;
					unsigned char BS;
					unsigned char STmin;
				}BIT;
			}FC_PCI;//FlowControl
			struct {
				unsigned char byte1;
				unsigned char byte2;
				unsigned char byte3;
			}BYTE;
		}PCI;
		PCIType_type PCIType;
	}N_PCI_type;
	typedef union{
		//normal addressing
		unsigned char Nml_SF_Data[7];//SingleFrame
		unsigned char Nml_FF_Data[6];//FirstFrame
		unsigned char Nml_CF_Data[7];//ConsecutiveFrame
		unsigned char Nml_FC_Data[5];//FlowControl
		//Normal fixed addressing
		unsigned char NF_SF_Data[7];//SingleFrame
		unsigned char NF_FF_Data[6];//FirstFrame
		unsigned char NF_CF_Data[7];//ConsecutiveFrame
		unsigned char NF_FC_Data[5];//FlowControl
		//Extended addressing
		unsigned char Ext_SF_Data[6];//SingleFrame
		unsigned char Ext_FF_Data[5];//FirstFrame
		unsigned char Ext_CF_Data[6];//ConsecutiveFrame
		unsigned char Ext_FC_Data[4];//FlowControl
		//Mixed addressing
		unsigned char Mix_SF_Data[7];//SingleFrame
		unsigned char Mix_FF_Data[6];//FirstFrame
		unsigned char Mix_CF_Data[7];//ConsecutiveFrame
		unsigned char Mix_FC_Data[5];//FlowControl
	}N_DATA_type;
	/*------------------- N_PDU ------------------*/
	typedef struct {
		N_AI_type N_AI;
		N_PCI_type	N_PCI;
		N_DATA_type N_DATA;
	}N_PDU_type;
	/*----------------- N_PDU end-----------------*/

/*--------------------�����Э�� end-------------------*/

#endif /* NETWORKTYPE_H_ */
