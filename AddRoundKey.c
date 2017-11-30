#include "common.h"
#include <stddef.h>

/**
 * @file AddRoundKey.c
 */

void AddRoundKey(state_t *state, block_t *key_schedule) {
     const int Nb = NB_SIZE;
     const int columns = state->columns;
     int i, j;

     for (i=0; i<Nb; i++) {
          for (j=0; j<columns; j++) {
          state->array[j][i] ^= key_schedule->array[(STATE_ROWS*j) + i];
          }
     }
}
