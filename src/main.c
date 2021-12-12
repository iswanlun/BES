#include "stdlib.h"
#include "env.h"
#include "rand.h"
#include "log.h"
#include "graphics.h"
#include "selector.h"

int main( int argc, char** argv ) { /* expects name of log file */

    /* temp vars */
    int generations = 1025, 
    iterations = 130, 
    x_dim = 128, 
    y_dim = 128, 
    population = 1000, 
    genome_size = 12,
    threads = 1,
    selector_type = 4;

    /* preform setup */
    if ( argc < 3 | log_init( argv[1] ) | graphics_init( argv[2] ) ) {
        exit(1);
    }

    rand_init( threads );
    environment* env = env_new( x_dim, y_dim );
    env_populate( env, population, genome_size );
    selector_init( env, selector_type );

    /* run a set of generations */
    for ( int i = 0; i < generations; ++i ) {

        /* run single generation, x number of iterations */
        env_run_generation( env, iterations );

        /* perform natural selection and breed new generation, setup next environment */
        env_regenerate( env );

        selector_update( env, selector_type );
    }

    /* preform shutdown */
    env_cleanup( env );
    rand_clean_up();

    return 0;
}