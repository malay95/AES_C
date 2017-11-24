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

#define NK_128 4
#define NB_128 4
#define NR_128 10

#define NK_192 6
#define NB_192 4
#define NR_192 12

#define NK_256 8
#define NB_256 4
#define NR_256 14

#define STATE_ROWS 4
#define NB_SIZE 4
#define OCTET 8

/* Bit manipulation operations */
#define GETBIT(integer, position) ((integer >> position ) & 0x01)
#define SETBIT(integer, position) integer |= (1 << position)
#define CLEARBIT(integer, position) integer &= ~(1 << position)
#define TOGGLEBIT(integer, position) integer ^= (1 << position)

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
     uint8_t array[STATE_ROWS][NB_SIZE];
     int rows;
     int columns;
} state_t;

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

int init_key(key_t *key, key_size_t key_size);
void init_block(block_t *block);
void init_struct(state_t *state);
uint8_t finite_mul(uint8_t a, uint8_t b);

#endif
