#include "stdio.h"
#include "stdlib.h"
#include "env.h"
#include "rand.h"
#include "log.h"

char east_selection( int x_dim, int y_dim ) {

    return ( y_dim > 125 ) ? 1:0;
}

int main( int argc, char** argv ) { /* expects name of log file */

    /* temp vars */
    int generations = 1, 
    iterations = 1, 
    width = 128, 
    length = 128, 
    population = 1000, 
    genome_size = 4, 
    threads = 1;
    char* log_path;

    /* preform setup */
    if ( argc < 2 | log_init( argv[1] ) ) {
        exit(1);
    }

    rand_init( threads );

    environment* env = env_new( width, length );
    env_populate( env, population, genome_size );
    env_select( env, &east_selection );

    for ( int i = 0; i < generations; ++i ) {

        /* run single generation, x number of iterations */
        env_run_generation( env, iterations );

        /* perform natural selection and breed new generation, setup next environment */
        env_regenerate( env );
    }

    /* preform shutdown */
    env_cleanup( env );

    return 0;
}