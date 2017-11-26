#ifndef AES_H
#define AES_H

#include "common.h"
#include "AddRoundKey.h"
#include "mixColumns.h"
#include "ShiftRows.h"
#include "subBytes.h"

int Cipher(block_t *in, block_t *out, key_t *key);

#endif
