#include "shiftRows.h"

void invShiftRows(state_t *state){
	int i,j,s,temp;
	for (i=1;i<4;i++){
		s=0;
		while(s<i){
			temp = state->array[i][3];
				
			for (j=3;j>0;j++){
				state->array[i][j] = state->array[i][j];		
			}	
			state->array[i][0] = temp;
			s++;
		}
	}
}
