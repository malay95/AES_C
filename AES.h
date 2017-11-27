#ifndef AES_H
#define AES_H

#include "common.h"
#include "AddRoundKey.h"
#include "mixColumns.h"
#include "ShiftRows.h"
#include "subBytes.h"

void copySubArray(uint8_t *, uint8_t *, int, int);

int Cipher(block_t *in, block_t *out, key_t *key);

int invCipher(block_t *in, block_t *out, key_t *key);

int keyExpansion (key_t *key);

#endif
