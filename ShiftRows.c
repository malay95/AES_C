#include "ShiftRows.h"

#define SHIFT(r,NB) r

void shiftRows(state_t *state) {
     int r,c;
     volatile uint8_t row[STATE_ROWS];

     for(r=1;r<STATE_ROWS;r++) {
          for(c=0;c<NB_SIZE;c++) {
               row[c] = state->array[r][(c+SHIFT(r,NB_SIZE) % NB_SIZE)];
          }
          for(c=0;c<NB_SIZE;c++) {
               state->array[r][c] = row[c];
          }
     }
}

void invShiftRows(state_t *state) {
     int r,c;
     volatile uint8_t row[STATE_ROWS];

     for(r=1;r<STATE_ROWS;r++) {
          for(c=0;c<NB_SIZE;c++) {
               row[c] = state->array[r][c];
          }
          for(c=0;c<NB_SIZE;c++) {
               state->array[r][(c+SHIFT(r,NB_SIZE) % NB_SIZE)] = row[c];
          }
     }
}

