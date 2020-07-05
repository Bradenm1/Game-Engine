#include "Hashing.h"

unsigned Hashing::Hash(const char* s)
{
    unsigned h = FIRSTH;
    while (*s) {
        h = (h * A) ^ (s[0] * B);
        s++;
    }
    return h; // or return h % C;
}
