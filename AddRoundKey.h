#ifndef ADDROUNDKEY_H
#define ADDROUNDKEY_H

#include "common.h"

/*
 * AddRoundkey performs a transformation to the state by XOR operations
 * @param state This is a state block for which the transformation will occur
 * @param_type state_t
 * @param key This is the key struct which contains the key schedule used in this
 *            operation.
 * @param_type key_t
 */
void AddRoundKey(state_t *state, key_t *key);

#endif
