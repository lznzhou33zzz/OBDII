/*
 * DataLink.h
 *
 *  Created on: 2013Äê11ÔÂ14ÈÕ
 *      Author: zezhongzhao
 */

#ifndef DATALINK_H_
#define DATALINK_H_

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
		unsigned long rsv:3;
	}Part;
	unsigned long whole_ID;
}ID_type;

typedef enum{
	Complete,
	Not_Complete
}Transfer_Status_type;


#endif /* DATALINK_H_ */
