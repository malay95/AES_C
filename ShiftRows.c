#include "ShiftRows.h"

/**
 * @file ShiftRows.c
 */

#define SHIFT(r,NB) r

void shiftRows(state_t *state) {
     int r,c;
     volatile uint8_t row[STATE_ROWS];

     for(r=1;r<STATE_ROWS;r++) {
          for(c=0;c<NB_SIZE;c++) {
               row[c] = state->array[((c+SHIFT(r,NB_SIZE)) % NB_SIZE)][r];
          }
          for(c=0;c<NB_SIZE;c++) {
               state->array[c][r] = row[c];
          }
     }
}

void invShiftRows(state_t *state) {
     int r,c;
     volatile uint8_t row[STATE_ROWS];

     for(r=1;r<STATE_ROWS;r++) {
          for(c=0;c<NB_SIZE;c++) {
               row[c] = state->array[c][r];
          }
          for(c=0;c<NB_SIZE;c++) {
               state->array[((c+SHIFT(r,NB_SIZE)) % NB_SIZE)][r] = row[c];
          }
     }
}

