#ifndef RAND_H
#define RAND_H

#include <stdint.h>

void rand_init( int thread_count ) ;

uint32_t rand_next( int thread ) ;

void rand_clean_up( void );

#endif