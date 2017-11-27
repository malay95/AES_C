#ifndef subBytes_h
#define subBytes_h

#include <stdint.h>
#include "common.h"

/** 
 * This function uses sbox and transforms the state  8 bit value
 * @param state it is a 2D array of values and they are passed as a reference. 
*/
void subBytes(state_t *);

/** 
 * @breif	This function uses inv_sbox and transforms the state  8 bit value
 * @param state it is a 2D array of values and they are passed as a reference. 
*/
void invSubBytes(state_t *);

#endif
