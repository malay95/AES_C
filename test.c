#include<stdint.h>
#include "common.h"
#include "mixColumns.h"
#include "subBytes.h"
#include <stdio.h>
void coef_multi(uint8_t *, uint8_t *, uint8_t *);
uint8_t finite_mul(uint8_t , uint8_t);
void coef_multi(uint8_t *a, uint8_t *b, uint8_t *d){
	d[0] = finite_mul(a[0],b[0]) ^ finite_mul(a[3],b[1]) ^ finite_mul(a[2],b[2]) ^ finite_mul(a[1],b[3]);
	d[1] = finite_mul(a[1],b[0]) ^ finite_mul(a[0],b[1]) ^ finite_mul(a[3],b[2]) ^ finite_mul(a[2],b[3]);
	d[2] = finite_mul(a[2],b[0]) ^ finite_mul(a[1],b[1]) ^ finite_mul(a[0],b[2]) ^ finite_mul(a[3],b[3]);
	d[3] = finite_mul(a[3],b[0]) ^ finite_mul(a[2],b[1]) ^ finite_mul(a[1],b[2]) ^ finite_mul(a[0],b[3]);
}

uint8_t finite_mul(uint8_t a, uint8_t b){
	uint8_t i,ans=0;
	uint8_t hb = 0; 
	for (i=0;i<8;i++){
		if (b & 1){
			ans = ans ^ a;		
		}	
		hb = a & 0x80;
		a = a << 1;
		if (hb) 
			a = a ^ 0x1b;		
		b=b>>1;
	}
	return ans;
}
int main(void){
	uint8_t a[] = {0x02,0x01,0x01,0x03};
	uint8_t b[] = {0xd4,0xbf,0x5d,0x30};
	uint8_t d[] = {0,0,0,0};
	coef_multi(a,b,d);	
	printf("%x %x %x %x\n",d[0],d[1],d[2],d[3]);
     return 0;
}

