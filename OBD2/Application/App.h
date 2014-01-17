/*
 * OBD.h
 *
 *  Created on: 2013Äê10ÔÂ14ÈÕ
 *      Author: zzz
 */

#ifndef OBD_H_
#define OBD_H_



typedef enum {
	Success,
	No_Success
}TransferStatus_type;

typedef struct{
	unsigned long ID;
	unsigned char DLC = 8;
	unsigned char  DATA[8];
	TransferStatus_type TransferStatus;
}DataLinkParameter_type;
/*-------- data type--------*/
typedef struct
{
	long Identifier;
	int Format;
	char DLC;
	char* Data;
}DataRequest_type;

typedef struct {
	long Identifier;
	int Format;
	char DLC;
	char* Data;
}DataIndication_type;

typedef struct {
char Identifier;
char Transfer_Status;
}DataConfirm_type;

typedef struct
{
	DataRequest_type Request;
	DataIndication_type Indication;
	DataConfirm_type Confirm;
}Data_type;
Data_type L_Data,MA_DATA;
/*-------- remote frame type--------*/
typedef struct{
long Identifier;
char Format;
char DLC;
}RemoteRequest_type;

typedef struct{
long Identifier;
int Format;
char DLC;
}RemoteIndication_type;

typedef struct{
long Identifier;
char Transfer_Status;
}RemoteConfirm_type;

typedef struct{
	RemoteRequest_type Request;
	RemoteIndication_type Indication;
	RemoteConfirm_type Confirm;
}Remote_type;
Remote_type L_Remote,MA_Remote;
/*-------- ovld frame type--------*/
typedef struct{
}OVLDRequest_TYPE;
typedef struct{
}OVLDIndication_type;
typedef struct
{
	char Transmission_Status;
}OVLDComfirm_type;
typedef struct{
	OVLDRequest_TYPE Request;
	OVLDIndication_type Indication;
	OVLDComfirm_type Comfirm;
};


a

#endif /* OBD_H_ */
