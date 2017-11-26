
#include "subBytes.h"
void subBytes(state_t * state){
	int i,j;
	
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			s_Box(state->array[i][j]); 	
		}	
	}
}
