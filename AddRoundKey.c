#include "common.h"
#include <stddef.h>

void AddRoundKey(state_t *state, block_t *key_schedule) {
     const int Nb = NB_SIZE;
     const int columns = state->columns;
     int i, j;
     uint8_t *state_column = NULL;
     uint8_t *block_column = NULL;

     for (i=0; i<Nb; i++) {
          state_column = &(state->array[i][0]);
          block_column = &(key_schedule->array[i]);
          for (j=0; j<columns; j++) {
               state_column[j] ^= block_column[j];
          }
     }
}
