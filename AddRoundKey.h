#ifndef ADDROUNDKEY_H
#define ADDROUNDKEY_H

#include "common.h"
/**
 * @file AddRoundKey.h
 * @brief This library module allows access to the AddRoundKey operation 
 *        of the AES NIST Standard Cipher. This is to be used with other
 *        AES operations to perform AES Encryption.
 */

/*
 * AddRoundkey performs a transformation to the state by XOR operations See 
 * Processing Standards Publication 197 Section 5.1.4 for more information on
 * the algorithim used here.
 *
 * @param state This is a state block for which the transformation will occur
 * @param key This is the key struct which contains the key schedule used in this
 *            operation.
 */
void AddRoundKey(state_t *state, block_t *key_schedule);

#endif
