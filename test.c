#include "AES.h"

int main(void)
{
     key_t key128, key192, key256;
     genSecureKey(&key128, KEY128);
     genSecureKey(&key192, KEY192);
     genSecureKey(&key256, KEY256);
}
