/*
 * common_macros.h
 *
 *  Created on: Apr 23, 2019
 *      Author: shahira ibrahim
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

#include "std_types.h"

//MACRO to set a specific bit in register
#define SET_BIT(REG,BIT_NUM)  (REG |=(1<<BIT_NUM))

//macro to clear a specific bit in register
#define CLEAR_BIT(REG,BIT_NUM) (REG &=~(1<<BIT_NUM))

//macro to toggle a specific bit in register
#define TOGGLE_BIT(REG,BIT_NUM) (REG ^=(1<<BIT_NUM))

//macro to check if the bit is set "equal to one"
#define BIT_IS_SET(REG,BIT_NUM) (REG&(1<<BIT_NUM))

//macro to check if the bit is cleared "equal to zero"
#define BIT_IS_CLEAR(REG,BIT_NUM) (!(REG&(1<<BIT_NUM)))

//macro to rotate a number to left with specific number of rotations
#define ROL(NUM,NUM_0F_ROTATIONS) (NUM=(NUM<<NUM_0F_ROTATIONS)|(REG>>(8*sizeof(NUM)-NUM_0F_ROTATIONS)))

//macro to rotate a number to right with specific number of rotations
#define ROR(NUM,NUM_0F_ROTATIONS) (NUM=(NUM>>NUM_0F_ROTATIONS)|(REG<<(8*sizeof(NUM)-NUM_0F_ROTATIONS)))

//macro to get the value of specific bit "whether it's one or  zero"
#define GET_BIT(NUM,BIT_NUM)   ((NUM&(1<<BIT_NUM))? (TRUE):(FALSE))

#endif /* COMMON_MACROS_H_ */
