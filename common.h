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

#endif
