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

/**
 * @file AES.h
 * @brief This library contains the functions to generate a secure
 *        AES key, encrypt a message into ciphertext, and convert
 *        a ciphertext back into a message.
 */

/**
 * genSecureKey takes a key_t structure and a key_size_t and 
 * initializes the key_t structure and then generates a secure 
 * AES key of size key_size.
 *
 * @note            This function is only designed to work on Linux versions
 *                  greater then 3.16. This does not work on non-linux systems.
 *
 * @param key       This is an address to a key structure that needs to be
 *                  initialized. Random key will be generated upon call. This
 *                  function is blocking if the Linux Entropy pool is not 
 *                  available yet.
 * @param key_size  This is the size of key you want to initialize and generate.
 *                  Valid sizes are { KEY128, KEY192, KEY256 }. Any other input
 *                  will result in this function failing.
 *
 * @return int      This function will return an integer; if the value is 0
 *                  the function has failed, if the value is 1 the function
 *                  has succeeded. 
 */
int genSecureKey(key_t *key, key_size_t key_size);

/**
 * Cipher is the function call that generates a Ciphertext from a Message and Key. 
 * Given a block of input and a key, this function will write to the output block 
 * the corresponding cipertext.
 *
 * @param in        This is an address to a block_t structure that contains the
 *                  message which should be converted into a ciphertext.
 * @param out       This is an address to a block_t structure that contains the
 *                  buffer for which the ciphertext should be written to.
 * @param key       This is the address for which the key_t structure is available
 *                  and which the Cipher will encrypt the message in block with.
 *
 * @return int      This function will return an integer; if the value is 0 the 
 *                  function has failed, if the value is 1 the function has succeeded.
 *
 */
int Cipher(block_t *in, block_t *out, key_t *key);

int InverseCipher (block_t *in, block_t *out, key_t *key);

int keyExpansion (key_t *key);

#endif
