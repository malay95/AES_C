#include <stdio.h>
#include "AES.h"

int main(void)
{
     key_t key128;
     block_t message, cipher, reverse;
     int i,j;
     uint8_t standard_key[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
     uint8_t standard_message[16] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
     //uint8_t standard_key[16] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
     //uint8_t standard_message[16] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
     uint8_t r_val[4];

     init_key(&key128, KEY128);
     init_block(&message);
     init_block(&cipher);
     init_block(&reverse);

     /* Copy standard_key to key_t */
     for (i=0;i<16;i++) {
          key128.key.key128.key[i] = standard_key[i];
          message.array[i] = standard_message[i];
     }

     Cipher(&message, &cipher, &key128);
     InverseCipher(&cipher, &reverse, &key128);


     for (i=0;i<30;i++)
     {
          rCon(i,r_val);
          printf("\nI=%d: {%02x,%02x,%02x,%02x}",i,r_val[0], r_val[1], r_val[2], r_val[3]);

     }

     return 0;
}
