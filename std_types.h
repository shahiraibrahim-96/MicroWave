/*
 * std_types.h
 *
 *  Created on: Apr 23, 2019
 *      Author: shahira ibrahim
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

//boolean datatype declaration
typedef unsigned char bool;

//boolean values
#ifndef TRUE
#define TRUE (1u)
#endif

#ifndef FALSE
#define FALSE (0u)
#endif

#ifndef HIGH
#define HIGH (1u)
#endif

#ifndef LOW
#define LOW  (0u)
#endif

#define NULL_PTR ((void*)0) //null pointer representation


//standard data type declaration
typedef unsigned char uint8;   /* 0---->255 */
typedef signed char   sint8;   /* -128----->0------>127  */
typedef unsigned short uint16; /* 0--->65535  */
typedef signed short  sint16;   /*  -32768----->0------>32767 */
typedef unsigned long uint32;   /*  0-------->4294967295 */
typedef signed long   sint32;   /*  -2147483648--------->0------------>2147483649 */
typedef unsigned long long  uint64;  /* 0----------->18446744073709551615 */
typedef signed long long sint64;
typedef float float32;
typedef double float64;



#endif /* STD_TYPES_H_ */
