#include "../memset.h"


void _memset(unsigned char* src, unsigned long amt, unsigned char val) {
    while (amt--) {
        *src++ = val;
    }
}
