
#include "mixColumns.h"

void mixColoumns(state_t *state){
	uint8_t a[] = {0x02,0x01,0x01,0x03};
	int i,j,col[4],res[4];
	
	for (j=0;j<4;j++){
		for (i=0;i<4;i++){
			col[i] = state->array[4*i + j];	
		}
		coef_multi(a,col,res);
		for (i=0;i<4;i++){
			state->array[4*i +j] = res[i];		
		}
	{

}  
