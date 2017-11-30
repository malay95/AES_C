
#include "mixColumns.h"

/**
 * @file mixColumns.c
 */

void mixColumns(state_t *state){
	uint8_t a[] = {0x02,0x01,0x01,0x03};
	int i,j;
	uint8_t col[4],res[4];
	
	for (j=0;j<4;j++){
		for (i=0;i<4;i++){
			col[i] = state->array[j][i];	
		}
		coef_multi(a,col,res);
		for (i=0;i<4;i++){
			state->array[j][i] = res[i];		
		}
	}

}  

void invMixColumns( state_t *state){
	uint8_t a[] = {0x0e,0x09,0x0d,0x0b};
	int i,j;
	uint8_t col[4],res[4];
	for (j=0;j<4;j++){
		for (i=0;i<4;i++){
			col[i] = state->array[j][i];		
		}	
		coef_multi(a,col,res);
		for (i=0;i<4;i++){
			state->array[j][i] = res[i];
		}
	}
}
