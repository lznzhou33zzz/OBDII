/*
 * CanIf_Types.h
 *
 *  Created on: 2013Äê12ÔÂ19ÈÕ
 *      Author: zzz
 */

#ifndef CANIF_TYPES_H_
#define CANIF_TYPES_H_


typedef enum{
	Complete,
	Not_Complete
}Transfer_Status_type;

typedef enum {
	byte0,byte1,byte2,byte3,
	byte4,byte5,byte6,byte7,
	byte8,byte12,byte16,byte20,
	byte24,byte32,byte48,byte64
}DataLth_type;

typedef enum{
	CBFF ,//Classical Base Frame format
	CEFF ,//Classical Extended Frame format
	FBFF ,//FD Base Frame format
	FEFF ,//FD Extended Frame format
}Formate_type;

typedef union{
	struct{
		unsigned long base_ID:11;
		unsigned long extended_ID:18;
	}Ext_ID;
	struct{
		unsigned long ID:11;
	}Nor_ID;
	unsigned long whole_ID;
}ID_type;

typedef struct{
	ID_type Identifier;
	Formate_type Format;
	DataLth_type DLC;
	unsigned char Data[64];
}L_SDU_DataReq_type;

typedef struct{
	ID_type Identifier;
	Formate_type Format;
	DataLth_type DLC;
	unsigned char Data[64];
}L_SDU_DataInd_type;

typedef struct{
	ID_type Identifier;
	Transfer_Status_type Tx_Status;
}L_SDU_DataCfm_type;

typedef struct{
	ID_type Identifier;
	Formate_type Format;
	DataLth_type DLC;
}L_SDU_RemoteReq_type;

typedef struct{
	ID_type Identifier;
	Formate_type Format;
	DataLth_type DLC;
}L_SDU_RemoteInd_type;

typedef struct{
	ID_type Identifier;
	Transfer_Status_type Tx_Status;
}L_SDU_RemoteCfm_type;


#endif /* CANIF_TYPES_H_ */
