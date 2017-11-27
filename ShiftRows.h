#ifndef SHIFT_ROWS_H
#define SHIFT_ROWS_H

#include "common.h"
/**
 * @file ShiftRows.h
 * @brief This library contains the functions to perform the ShiftRows AES operation
 *        as well as how to invert the ShiftRows operation. 
 */

/**
 * shiftRows takes the state_t struct for the current AES operation and performs
 * the transform on the data in the state. All operations are done on the state
 *
 * @param state     This is a state block for which the ShiftRows transformation
 *                  will occur.
 */
void shiftRows(state_t *state);

/**
 * invShiftRows takes the state_t struct for the current AES operation and performs
 * the transform on the data in the state. All operations are done on the state
 *
 * @param state     This is a state block for which the InvShiftRows transformation
 *                  will occur.
 */
void invShiftRows(state_t *state);

#endif
