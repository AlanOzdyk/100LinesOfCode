#include <stdio.h>
#include <stdint.h>

static uint32_t state = 1;


void mysRand(uint32_t seed) {
    if (seed) state = seed;
}


uint32_t myRand() {
    uint32_t x = state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state = x;
    return x;
}

uint32_t myRandRange(uint32_t max) {
    return myRand() % max;
}

int main() {
    mysRand(1);

    for (int i = 0; i < 10; i++) {
        printf("%u\n", myRandRange(10000));
    }

    return 0;
}