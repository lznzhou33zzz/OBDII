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
	base,
	extended,
	FDbase,
	FDextended
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





#endif /* CANIF_TYPES_H_ */
