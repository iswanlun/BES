#include "stdlib.h"
#include "env.h"
#include "rand.h"
#include "log.h"
#include "graphics.h"

char east_selection( int x_dim, int y_dim ) {

    return ( x_dim > 100 ) ? 1:0;
}

int main( int argc, char** argv ) { /* expects name of log file */

    /* temp vars */
    int generations = 1000, 
    iterations = 180, 
    width = 128, 
    length = 128, 
    population = 700, 
    genome_size = 8,
    threads = 1;

    /* preform setup */
    if ( argc < 3 | log_init( argv[1] ) | graphics_init( argv[2] ) ) {
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