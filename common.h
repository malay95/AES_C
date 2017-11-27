#ifndef COMMON_H
#define COMMON_H

#define __key_t_defined
#define _KEY_T_DECLARED

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
#define WORD_SIZE 4

/* Bit manipulation operations */
#define GETBIT(integer, position) ((integer >> position ) & 0x01)
#define SETBIT(integer, position) integer |= (1 << position)
#define CLEARBIT(integer, position) integer &= ~(1 << position)
#define TOGGLEBIT(integer, position) integer ^= (1 << position)

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

/** 
 *  @file		common.h
 *  @brief	This file contains all commonly shared data structures as well as
 *             all commonly reused functions such as array xors and array comparison
 *             operations.
 */


/** 
 * This function which takes 1 parameter and returns the sbox transformation of the 8 bit number 
 * 
 * @param a is a unsigned int of 8 bits
 * @retval unsigned integer of 8 bits 
*/
uint8_t s_Box(uint8_t);


/** 
 * A function which takes 1 parameter and returns the inverse sbox transformation of the 8 bit integer 
 * 
 * @param a is a unsigned int of 8 bits
 * @retval unsigned integer of 8 bits 
*/
uint8_t inv_s_Box(uint8_t);

/** 
 * coefficients multiplication over modulo x4 +1
 * output will be in the form of a finite field. 
 * 
 * @param a is the fixed polynomial a(x) 
 * @param b is the input polynomial b(x)
 * @param d the multiplication of a and b modulo x4 + 1
*/
void coef_multi(uint8_t *, uint8_t *,uint8_t *);

/** 
 * This function applies the s_box on a 4 byte word 
 * 
 * @param a 4-byte word (This is a pointer of type uint8_t to an array of 4 uint8_t's)
*/
void subWord(uint8_t *);

/** 
 * Permutes the word i.e. [a0,a1,a2,a3] changes to [a1,a2,a3,a0]
 *
 * @param a 4-byte word (This is a pointer of type uint8_t to an array of 4 uint8_t's)
*/
void rotWord(uint8_t *);

/**
@fucntion rCon
@breif 	  the round constant word array contains the values given by [x^i-1, 00 ,00,00]
@param	  i - power. starts from 1
@param 	  r - output word   
*/
void rCon(int , uint8_t *);

/**
 * This enumeration is of the type of AES being performed (Key Size being used)
 * AES128, AES192, and AES256 are entirely implemented from the NIST standard.
 */
typedef enum {
     KEY128 = 0, /**< Use AES 128, give key size of 128 bits */
     KEY192 = 1, /**< Use AES 192, give key size of 192 bits */
     KEY256 = 2 /**< Use AES 256, give key size of 256 bits */
} key_size_t;

/**
 * This struct is typed for a Block as defined in the AES standard of 128 bits. It
 * includes a size value. This is used for all parts of the AES algorithm, 
 * including input and output.
 */
typedef struct {
     uint8_t array[BLOCK_SIZE]; /**< Actual block of data is a 1-D array of uint8_t */
     int size; /**< Value of the size of the array, this value is fixed on init at 16 */
} block_t;

/** 
 * This struct is typed for a State Block as described in the AES standard, it is 
 * a fixed 2-D array of 4x4 uint8_t. This is used during the rounds process of the
 * AES algorithm. 
 *
 * @NOTE: This struct should not be created by an end user.
 */
typedef struct {
     uint8_t array[STATE_ROWS][NB_SIZE]; /**< 2-D Array 4x4 uint8_t to hold the state */
     int rows; /**< size of the rows of this array */
     int columns; /**< size of the columns of this array */
} state_t;

/**
 * This struct is typed for a key sized of 128 bits. It also includes the buffer for the
 * expanded AES key generated during the Cipher and InvCiper functions. The values for
 * Nk~Nr are generated on init and never change.
 */
typedef struct {
     uint8_t key[KEY128_SIZE]; /**< The 128 bit 1-D array that holds the AES key */
     uint8_t expanded_key[WORD_SIZE * NB_128 * (NR_128 + 1)]; /**< The simulated 2-D array 
                                                                via a 1-D array for holding the 
                                                                expanded key */
     int size; /**< Constant value created on init based on key size of 128 */
     int Nk; /**< Constant value created on init based on values in init document. Nk=4  */
     int Nb; /**< Constant value created on init based on values in init document. Nb=4  */
     int Nr; /**< Constant value created on init based on values in init document. Nr=10 */
} key128_t;

/**
 * This struct is typed for a key sized of 192 bits. It also includes the buffer for the
 * expanded AES key generated during the Cipher and InvCiper functions. The values for
 * Nk~Nr are generated on init and never change.
 */
typedef struct {
     uint8_t key[KEY192_SIZE]; /**< The 192 bit 1-D array that holds the AES key */
     uint8_t expanded_key[WORD_SIZE * NB_192 * (NR_192 + 1)];  /**< The simulated 2-D array·
                                                                 via a 1-D array for holding the
                                                                 expanded key */
     int size; /**< Constant value created on init based on key size of 192 */
     int Nk; /**< Constant value created on init based on values in init document. Nk=6  */
     int Nb; /**< Constant value created on init based on values in init document. Nb=4  */
     int Nr; /**< Constant value created on init based on values in init document. Nr=12 */
} key192_t;

/**
 * This struct is typed for a key sized of 256 bits. It also includes the buffer for the
 * expanded AES key generated during the Cipher and InvCiper functions. The values for
 * Nk~Nr are generated on init and never change.
 */
typedef struct {
     uint8_t key[KEY256_SIZE]; /**< The 256 bit 1-D array that holds the AES key */
     uint8_t expanded_key[WORD_SIZE * NB_256 * (NR_256 + 1)]; /**< The simulated 2-D array·
                                                                via a 1-D array for holding the
                                                                expanded key */
     int size; /**< Constant value created on init based on key size of 256 */
     int Nk; /**< Constant value created on init based on values in init document. Nk=8  */
     int Nb; /**< Constant value created on init based on values in init document. Nb=4  */
     int Nr; /**< Constant value created on init based on values in init document. Nr=14 */
} key256_t;

/**
 * This struct is a typed key data type which holds an enumeration on the key stored as well
 * as a union of all three possible key types.
 */
typedef struct {
     key_size_t key_size; /**< Enumeration of key size; Valid inputs are { KEY128, KEY192, KEY256 } */
     union { /**< Union of various sized Key_t */
          key128_t key128;
          key192_t key192;
          key256_t key256;
     } key;
} key_t;

/** 
 * A function which takes the address of a key_t and initialize the structure.
 * @NOTE: THIS DOES NOT GENERATE A KEY, it just initializes the structure. 
 * 
 * @param key       This is an address to an uninitialized key_t structure 
 * @param key_size  An enumeration of the key size to be initialized
 * 
 * @return int      This function will return an integer; if the value is 0
 *                  the function has failed, if the value is 1 the function
 *                  has succeeded.
*/
int init_key(key_t *key, key_size_t key_size);

/**
 * A function which takes the address of a block_t and initializes the structure.
 *
 * @param block     This is an address to an uninitialized block_t structure
 */
void init_block(block_t *block);

/**
 * A function which takes the address of a state_t struct and initializes the structure.
 *
 * @param state     This is an address to an uninitialized struct_t structure.
 */
void init_state(state_t *state);

/**
 * A function which takes two unsigned byte integers and performa modular multiplication
 * on them using the method described in Section 4.2 of Processing Standards Publication 197.
 * Generates a GF(2^8) field which it performs multiplication with a irreducible 
 * polynomial of degree 8.
 *
 * @param a         This is a uint8_t which is going to be multiplied by b.
 * @param b         This is a uint8_t which is going to be multiplied by a.
 *
 * @return int      This is the result of the multiplication and modulos 
 *                  operation on a and b. This is a uint8_t.
 */
uint8_t finite_mul(uint8_t a, uint8_t b);

#endif
