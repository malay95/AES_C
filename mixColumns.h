#ifndef mixColumns_h
#define mixColumns_h

#include <stdint.h>
#include "common.h"

/** 
@file mixColumns
@breif This function transforms on the state column by column and treating each column as a polynimial and
       multiplied by a fixed polynomial a(x) modulo x^4 + 1
@param the state is defined in the common.h file
*/

void mixColumns (state_t *);

/**
@name invMixColumns
@breif	Transformation in the inverse cipher that is the inverse of inverse of MixColumns
@param 	state variable 
*/

void invMixColumns (state_t *);
 
#endif
