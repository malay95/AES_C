/**
@file subBytes.c
This function uses sbox and transforms the state  16 bit value
@param state it is a 2D array of values and they are passed as a reference. 

*/

#include <stdint.h>
#include <common.h>
void subBytes(uint16_t * state){
	int i,j;
	
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			s_Box(state[i*4 + j]); 	
		}	
	}
}
