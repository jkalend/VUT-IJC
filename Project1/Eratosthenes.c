// Eratosthenes.c
// Řešení IJC-DU1, příklad a), 16.3.2022
// Autor: Jan Kalenda, FIT
// Přeloženo: gcc 11.2
// stredniky za setbit jsou nutne pro inline


#include "bitset.h"
#include "Eratosthenes.h"

void Eratosthenes(bitset_t pole) {
    unsigned long max = sqrt(bitset_size(pole));

    bitset_setbit(pole, 0, 1);
    bitset_setbit(pole, 1, 1);

    for(unsigned long i = 2*2; i < bitset_size(pole); i+=2) {
        bitset_setbit(pole, i, 1);
    }

    for (unsigned long i = 3; i <= max; i++) {

        if (!(bitset_getbit(pole, i))) {
            for (unsigned long j = i*i; j < bitset_size(pole); j += 2*i) {
                bitset_setbit(pole, j, 1);
            }
        }
    }

}
