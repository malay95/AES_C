#include "AES.h"

void copySubArray(uint8_t *in, uint8_t *out, int from, int to){
     int i;
     for (i=from;i<to;i++) {
          out[i] = in[i];
     }
     return;
}

int keyExpansion(key_t *key) {
     const key_size_t key_size = key->key_size;
     int Nk;
     int Nb;
     uint8_t *key_array;
     uint8_t *w;

     if (key_size == KEY128) {
          Nb = key->key.key128.Nb;
          Nk = key->key.key128.Nk;
          key_array = key->key.key128.key;
          w = key->key.key128.expanded_key;
     } else if(key_size == KEY192) {
          Nb = key->key.key192.Nb;
          Nk = key->key.key192.Nk;
          key_array = key->key.key192.key;
          w = key->key.key192.expanded_key;
     } else if (key_size == KEY256) {
          Nb = key->key.key256.Nb;
          Nk = key->key.key256.Nk;
          key_array = key->key.key256.key;
          w = key->key.key256.expanded_key;
     } else {
          /* Error condition Return Fail */
          return 0;
     }

     /* Success return as such */
     return 1;
}

int Cipher(block_t *in, block_t *out, key_t *key) {
     state_t state;
     key_size_t key_size = key->key_size;
     block_t key_schedule;
     uint8_t *w;
     int Nb;
     int Nk;
     int Nr;
     int r,c;

     /* Init the state and values */
     init_state(&state);
     key_size = key->key_size;
     keyExpansion(key);
     if (key_size == KEY128) {
          Nb = key->key.key128.Nb;
          Nk = key->key.key128.Nk;
          Nr = key->key.key128.Nr;
          w = key->key.key128.expanded_key;
     } else if(key_size == KEY192) {
          Nb = key->key.key192.Nb;
          Nk = key->key.key192.Nk;
          Nr = key->key.key192.Nr;
          w = key->key.key192.expanded_key;
     } else if (key_size == KEY256) {
          Nb = key->key.key256.Nb;
          Nk = key->key.key256.Nk;
          Nr = key->key.key256.Nr;
          w = key->key.key256.expanded_key;
     } else {
          /* Error condition Return Fail */
          return 0;
     }

     /* 
      * copy in block to state:
      *   state = in
      */
     for(r=0;r<STATE_ROWS;r++){
          for(c=0;c<Nb;c++) {
               state.array[r][c] = in->array[(r*STATE_ROWS)+c];
          }
     }

     copySubArray(w,key_schedule.array,0, Nb-1);
     AddRoundKey(&state, &key_schedule);

     for(r=1;r<Nr;r++) {
          subBytes(&state);
          shiftRows(&state);
          mixColumns(&state);
          copySubArray(w, key_schedule.array,r*Nb, (r+1)*Nb-1);
          AddRoundKey(&state, &key_schedule);
     }

     subBytes(&state);
     shiftRows(&state);
     copySubArray(w, key_schedule.array,Nr*Nb, (Nr+1)*Nb-1);
     AddRoundKey(&state, &key_schedule);

     
     for(r=0;r<STATE_ROWS;r++) {
          for(c=0;c<Nb;c++) {
               out->array[(r*STATE_ROWS)+c] = state.array[r][c];
          }
     }

}

