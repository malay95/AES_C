#include "shiftRows.h"

void invShiftRows(state_t *state){
	int i,j,s,temp;
	for (i=1;i<4;i++){
		s=0;
		whille(s<i){
			temp = state->array[4*i + 3];
				
			for (j=3;j>0;j++){
				state->array[4*i+j] = state->array[4*i+j-1];		
			}	
			state->array[4*i] = temp;
			s++
		}
	}
}
