#include "AES.h"

void copySubArray(uint8_t *in, uint8_t *out, int from, int to){
     int i,r;
     for (r=from;r<=to;r++) {
          for (i=0;i<WORD_SIZE;i++) {
               out[((r-from)*WORD_SIZE)+i] = in[(r*WORD_SIZE)+i];
          }
     }
     return;
}


void arrayXor (uint8_t *a, uint8_t *b,uint8_t *out,int l){
	int i;
	for (i=0;i<l;i++){
		out[i]= a[i] ^ b[i];
	}
}

int keyExpansion(key_t *key) {
     const key_size_t key_size = key->key_size;
     int Nk;
     int Nb;
     int Nr;
	uint8_t temp[WORD_SIZE], temp1[WORD_SIZE];
     uint8_t *key_array;
     uint8_t *w;
	int i,k;
	uint8_t r[WORD_SIZE];

     if (key_size == KEY128) {
          Nb = key->key.key128.Nb;
          Nk = key->key.key128.Nk;
          Nr = key->key.key128.Nr;
          key_array = key->key.key128.key;
          w = key->key.key128.expanded_key;
     } else if(key_size == KEY192) {
          Nb = key->key.key192.Nb;
          Nk = key->key.key192.Nk;
          Nr = key->key.key192.Nr;
          key_array = key->key.key192.key;
          w = key->key.key192.expanded_key;
     } else if (key_size == KEY256) {
          Nb = key->key.key256.Nb;
          Nk = key->key.key256.Nk;
          Nr = key->key.key256.Nr;
          key_array = key->key.key256.key;
          w = key->key.key256.expanded_key;
     } else {
          /* Error condition Return Fail */
          return 0;
     }
	
	for (i=0;i<Nk;i++){
		for (k=0;k<WORD_SIZE;k++){
			w[(WORD_SIZE*i)+k] = key_array[(WORD_SIZE*i)+k];	
		}
	}
	for (i=Nk;i<Nb*(Nr+1);i++){
		for (k=0;k<WORD_SIZE;k++){
			temp[k] = w[(WORD_SIZE*(i-1)) + k]; 		
		}
		if (i % Nk == 0){
			rCon((int)(i/Nk),r);
			copySubArray(temp,temp1,0,0);
			rotWord(temp1);			
			subWord(temp1);
			arrayXor(temp1,r,temp,WORD_SIZE);
		}else if (Nk > 6 && i%Nk == 4){
			subWord(temp);		
		}
		arrayXor(&w[WORD_SIZE * (i-Nk)],temp,&w[WORD_SIZE * i],WORD_SIZE);
	}
	return 1;
}	
     

     /* Success return as such */

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

     return 1;
}

int InverseCipher (block_t *in, block_t *out, key_t *key){
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

     copySubArray(w,key_schedule.array,Nr*Nb, (Nr+1)*Nb-1);
     AddRoundKey(&state, &key_schedule);

     for(r=1;r<Nr;r++) {
		invShiftRows(&state);
		invSubBytes(&state);
		copySubArray(w,key_schedule.array, r*Nb , (r+1)*Nb-1);
		AddRoundKey(&state,&key_schedule);
		invMixColumns(&state);
     }

     invShiftRows(&state);
	invSubBytes(&state);
     copySubArray(w, key_schedule.array,0, Nb-1);
     AddRoundKey(&state, &key_schedule);

     
     for(r=0;r<STATE_ROWS;r++) {
          for(c=0;c<Nb;c++) {
               out->array[(r*STATE_ROWS)+c] = state.array[r][c];
          }
     }

     return 0;
}

#define getrandom(buf, size, flags) syscall(SYS_getrandom, buf, size, flags)

int genSecureKey(key_t *key, key_size_t key_size) {
     size_t buffer_size;
     size_t buffer_returned = 0;
     uint8_t *key_array;
     init_key(key, key_size);
     if (key_size == KEY128) { 
          buffer_size = KEY128_SIZE;
          key_array = key->key.key128.key;
     } else if (key_size == KEY192) {
          buffer_size = KEY192_SIZE;
          key_array = key->key.key192.key;
     } else if (key_size == KEY256) {
          buffer_size = KEY256_SIZE;
          key_array = key->key.key256.key;
     }
     else {
          /* Error condition occured, return as such */
          return 0;
     }
     
     buffer_returned = getrandom(key_array, buffer_size, 0);
     if (buffer_returned != buffer_size) { 
          /* Error condition occured, return as such */
          return 0;
     }

     /* Function completed successfully */
     return 1;
}
