/*****************************************************************************
 * DISCLAIMER
 *
 * This software is supplied by Renesas Electronics Corporation and is only
 * intended for use with Renesas products. No other uses are authorized.
 * This software is owned by Renesas Electronics Corporation and is protected
 * under all applicable laws, including copyright laws.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
 * REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 * INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY
 * DISCLAIMED.
 *
 * TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
 * ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
 * FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES
 * FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS
 * AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 * Renesas reserves the right, without notice, to make changes to this
 * software and to discontinue the availability of this software.
 * By using this software, you agree to the additional terms and
 * conditions found by accessing the following link:
 * http://www.renesas.com/disclaimer
 *****************************************************************************/
/* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.  */
/*****************************************************************************
 * System Name  :
 * File Name    : Std_Types.h
 * Abstract     : Definitions of standard types used in whole platform.
 * Version      : 1.00
 * Device       :
 * Tool-Chain   :
 * OS           : none
 * H/W Platform :
 * Description  : This file defines standard types.
 * Operation    : none
 * Limitation   :
 *****************************************************************************
 * History      :
 *****************************************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H

/*****************************************************************************
 Includes   <System Includes> , "Project Includes"
 *****************************************************************************/


/*****************************************************************************
 Typedef definitions
 *****************************************************************************/

/* ---- MCU platform based type ---- */
typedef unsigned char boolean;
typedef signed char sint8;
typedef unsigned char uint8;
typedef signed short sint16;
typedef unsigned short uint16;
typedef signed long sint32;
typedef unsigned long uint32;
typedef signed long long sint64;
typedef unsigned long long uint64;
typedef float float32;
typedef double float64;

/* ---- Standard return type ---- */
typedef sint32 Std_ReturnType;

/*****************************************************************************
 Macro definitions
 *****************************************************************************/
/* ---- Symbols ---- */
#ifndef E_OK    /* for consideration of itron.h */
#define E_OK                          0L
#endif
#define E_NOT_OK                      (-1)

#ifndef TRUE
#define TRUE                          1
#endif
#ifndef FALSE
#define FALSE                         0
#endif

#define STD_HIGH                      0x01U	/* Physical state 5V or 3.3V */
#define STD_LOW                       0x00U	/* Physical state 0V */

#define STD_ACTIVE                    0x01U	/* Logical state active */
#define STD_IDLE                      0x00U	/* Logical state idle */

#define STD_ON                        0x01U
#define STD_OFF                       0x00U

#ifndef NULL
#define NULL           			      ((void*) 0U)
#endif

#ifndef NULL_PTR
#define NULL_PTR                      ((void*) 0U)
#endif

#endif /* STD_TYPES_H */
/* End of File */
