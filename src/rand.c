
#include "rand.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    uint32_t x, y, z, w;
} seed;

static seed* seeds;

void rand_init( int thread_count ) {

    seeds = (seed*) calloc( thread_count, sizeof(seed) );

    for ( int i = 0; i < thread_count; ++i ) {

        seeds[i].x = time(NULL);
        seeds[i].y = getpid() ^ getppid();
        seeds[i].y ^= (i) ? seeds[i-1].w : 0;
        seeds[i].z = clock();
        seeds[i].w = seeds[i].z ^ seeds[i].y;
    }
}

uint32_t rand_next( int thread ) {
    uint32_t t = seeds[thread].x;
    t ^= t << 11;
    t ^= t >> 8;
    seeds[thread].x = seeds[thread].y; 
    seeds[thread].y = seeds[thread].z;
    seeds[thread].z = seeds[thread].w;
    seeds[thread].w ^= seeds[thread].w >> 19;
    seeds[thread].w ^= t;
    return seeds[thread].w;
}

void rand_clean_up( void ) {
    free( seeds );
}