#include "stdlib.h"
#include "env.h"
#include "rand.h"
#include "log.h"

char east_selection( int x_dim, int y_dim ) {

    return ( y_dim > 64 ) ? 1:0;
}

int main( int argc, char** argv ) { /* expects name of log file */

    /* temp vars */
    int generations = 1, 
    iterations = 30, 
    width = 128, 
    length = 128, 
    population = 50, 
    genome_size = 4,
    threads = 1;

    /* preform setup */
    if ( argc < 2 | log_init( argv[1] ) ) {
        exit(1);
    }

    rand_init( threads );
    environment* env = env_new( width, length );
    env_populate( env, population, genome_size );
    env_select( env, &east_selection );

    /* run a set of generations */
    for ( int i = 0; i < generations; ++i ) {

        /* run single generation, x number of iterations */
        env_run_generation( env, iterations );

        /* perform natural selection and breed new generation, setup next environment */
        env_regenerate( env );
    }

    /* preform shutdown */
    env_cleanup( env );
    rand_clean_up();

    return 0;
}