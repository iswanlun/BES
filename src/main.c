#include "stdio.h"
#include "env.h"
#include "rand.h"

char east_selection( int x_dim, int y_dim ) {

    return ( y_dim > 125 ) ? 1:0;
}

int main( int argc, char** argv ) {

    int generations, iterations, width, length, population, genome_size, threads;

    /* preform setup */
    rand_init( threads );

    environment* env = env_new( width, length );
    env_populate( env, population, genome_size );
    env_select( env, &east_selection );

    for ( int i = 0; i < generations; ++i ) {

        /* run single generations, x number of iterations */
        env_run_iterations( env, iterations );

        /* perform natural selection and breed new generation, setup next environment */
        env_regenerate( env );
    }

    /* preform shutdown */
    env_cleanup( env );

    return 0;
}