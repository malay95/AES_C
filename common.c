#include "common.h"

int init_key(key_t *key, key_size_t key_size) {
     if (key_size == KEY128) {
          key128_t *key_t = &(key->key.key128);
          key->key_size = KEY128;
          key_t->size = KEY128_SIZE;
          key_t->Nk = 4;
          key_t->Nb = 4;
          key_t->Nr = 10;
          return 1;
     }
     else if (key_size == KEY192) {
          key192_t *key_t = &(key->key.key192);
          key->key_size = KEY192;
          key_t->size = KEY192_SIZE;
          key_t->Nk = 6;
          key_t->Nb = 4;
          key_t->Nr = 12;
          return 1;
     }
     else if (key_size == KEY256) {
          key256_t *key_t = &(key->key.key256);
          key->key_size = KEY256;
          key_t->size = KEY256_SIZE;
          key_t->Nk = 8;
          key_t->Nb = 4;
          key_t->Nr = 14;
          return 1;
     }
     else {
          /* An Error condition as occured, return as such */
          return 0;
     }
}

void init_block(block_t *block) {
     block->size = BLOCK_SIZE;
}

void init_struct(state_t *state) {
     state->rows = STATE_ROWS;
     state->columns = NB_SIZE;
}

/*
uint8_t polynomial_multiply(uint8_t a, uint8_t b) {
     volatile uint8_t gf[OCTET];
     volatile int i,j;
     volatile int set_bit;
     /\* Clear the GF field *\/
     for(i=0;i<OCTET;i++) {
          gf[i] = 0x00;
     }
     for (i=0;i<OCTET;i++) {
          /\* i is position of the bit of octet b *\/
          for (j=0;j<OCTET;j++) {
               /\* j is the position of bit of octet a *\/
               if( GETBIT(a,j) == 1) {
                    set_bit = j + i;

               }

          }
     }
}
*/

uint8_t xtime(uint8_t value)
{
     uint8_t temp = value << 1;
     if(GETBIT(value, 7) == 1){
          temp ^= 0x1b;
     }
     return temp;
}

uint8_t polynomial_multiply(uint8_t a, uint8_t b) {
     volatile uint8_t gf[OCTET];
     volatile int i;
     volatile uint8_t result = 0;

     gf[0] = a;
     for(i=1;i<OCTET;i++){
          gf[i] = xtime(gf[i-1]);
     }

     for (i=0;i<OCTET;i++){
          if(GETBIT(b,i) == 1) {
               result ^= gf[i];
          }
     }

     return result;
}
