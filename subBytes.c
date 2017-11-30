
#include "subBytes.h"

/**
 * @file subBytes.c
 */

void subBytes(state_t * state){
	int i,j;
	
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			state->array[i][j] = s_Box(state->array[i][j]);
		}	
	}
}

void invSubBytes(state_t * state){
	int i,j;
	
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			state->array[i][j] = inv_s_Box(state->array[i][j]); 	
		}	
	}
}
