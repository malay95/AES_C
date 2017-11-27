#ifndef AES_H
#define AES_H

#define _GNU_SOURCE

#include <sys/syscall.h>
#include <linux/random.h>
#include "common.h"
#include "AddRoundKey.h"
#include "mixColumns.h"
#include "ShiftRows.h"
#include "subBytes.h"

int genSecureKey(key_t *key, key_size_t key_size);
int Cipher(block_t *in, block_t *out, key_t *key);

#endif
