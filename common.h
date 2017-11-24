/** 
 *  @file		common.h
 *  @brief	This file contains all commonly shared data structures as well as
 *             all commonly resued functions such as array xors and array comparison
 *             operations.
 */

#ifndef COMMON_H
#define COMMON_H

#define BLOCK_SIZE 16
#define KEY128_SIZE 16
#define KEY192_SIZE 24
#define KEY256_SIZE 32

#include <stdint.h>

/** This function which takes 1 pararmeter and returns the sbox transformation of the 16 bit number 
@param a is a unsigned int of 16 bits
@retval unsigned integer of 16 bit 
*/
uint8_t s_Box(uint8_t);


/** A function which takes 1 pararmeter and returns the inverse sbox transformation of the 16 bit 		  integer 
@param a is a unsigned int of 16 bits
@retval unsigned integer of 16 bit 
*/
uint8_t inv_s_Box(uint8_t);

/** 
@breif coefficients multiplication over modulo x4 +1
	output will be in the form of a finite field. 
@param a is the fixed polynomial a(x) 
@param b is the input polynomial b(x)
@param d the multiplication of a and b modulo x4 + 1
*/
void coef_multi(uint8_t *, uint8_t *,uint8_t *);

/** 
@function subWord
@breif this function appplies the s_box on a 4 byte word 
@param a 4-byte word
*/
void subWord(uint8_t *);

/** 
@function rotWord
@breif Permutes the word i.e. [a0,a1,a2,a3] changes to [a1,a2,a3,a0]
@param a 4-byte word
*/
void rotWord(uint8_t *);

typedef enum {KEY128 = 0, KEY192 = 1, KEY256 = 2 } key_size_t;


typedef struct {
     uint8_t array[BLOCK_SIZE];
     int size;
} block_t;

typedef struct {
     uint8_t key[KEY128_SIZE];
     int size;
     int Nk;
     int Nb;
     int Nr;
} key128_t;

typedef struct {
     uint8_t key[KEY192_SIZE];
     int size;
     int Nk;
     int Nb;
     int Nr;
} key192_t;

typedef struct {
     uint8_t key[KEY256_SIZE];
     int size;
     int Nk;
     int Nb;
     int Nr;
} key256_t;

typedef struct {
     key_size_t key_size;
     union {
          key128_t key128;
          key192_t key192;
          key256_t key256;
     } key;
} key_t;

int init_key(key_t *key, key_size_t key_size)
{
     if (key_size == KEY128)
     {
          key128_t *key_t = &(key->key.key128);
          key->key_size = KEY128;
          key_t->size = KEY128_SIZE;
          key_t->Nk = 4;
          key_t->Nb = 4;
          key_t->Nr = 10;
          return 1;
     }
     else if(key_size == KEY192)
     {
          key192_t *key_t = &(key->key.key192);
          key->key_size = KEY192;
          key_t->size = KEY192_SIZE;
          key_t->Nk = 6;
          key_t->Nb = 4;
          key_t->Nr = 12;
          return 1;
     }
     else if(key_size == KEY256)
     {
          key256_t *key_t = &(key->key.key256);
          key->key_size = KEY256;
          key_t->size = KEY256_SIZE;
          key_t->Nk = 8;
          key_t->Nb = 4;
          key_t->Nr = 14;
          return 1;
     }
     else
     {
          /* An Error condition as occured, return as such */
          return 0;
     }
}

void init_block(block_t *block)
{
     block->size = BLOCK_SIZE;
}

void array_xor(uint8_t *a,uint8_t *b,uint8_t d, int n){
	int i;
	for (i=0;i<n;i++){
		d[i] = a[i] ^ b[i];	
	}
}

#endif
