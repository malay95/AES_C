#ifndef subBytes.h
#define subBytes.h

#include <stdint.h>
#include <common.h>

/** 
@file 	subBytes.c
@breif	This function uses sbox and transforms the state  16 bit value
@param state it is a 2D array of values and they are passed as a reference. 
*/

void subBytes(state_t *);

#endif
