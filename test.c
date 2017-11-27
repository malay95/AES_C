#include <stdio.h>
#include "AES.h"

int main(void)
{
     key_t key128;
     block_t message, cipher;
     int i;
     uint8_t standard_key[16] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
     uint8_t standard_message[16] = {0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};

     init_key(&key128, KEY128);
     init_block(&message);
     init_block(&cipher);

     /* Copy standard_key to key_t */
     for (i=0;i<16;i++) {
          key128.key.key128.key[i] = standard_key[i];
          message.array[i] = standard_message[i];
     }

     Cipher(&message, &cipher, &key128);



     return 0;
}
