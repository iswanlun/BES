#include "stdlib.h"
#include "env.h"
#include "rand.h"
#include "log.h"
#include "graphics.h"
#include "selector.h"
#include "setup.h"

int main( int argc, char** argv ) { /* expects name of log file */

    /* preform setup */
    if ( config_init( argv[1] ) ) {
        exit(1);
    }

    rand_init( 1 );
    environment* env = env_new( main_cfg.x_dim, main_cfg.y_dim );
    env_populate( env, main_cfg.population, main_cfg.genome_size );
    selector_init( env, main_cfg.selector_type );

    /* run a set of generations */
    for ( int i = 0; i < main_cfg.generations; ++i ) {

        /* run single generation, x number of iterations */
        env_run_generation( env, main_cfg.iterations );

        /* perform natural selection and breed new generation, setup next environment */
        env_regenerate( env );

        selector_update( env, main_cfg.selector_type );
    }

    /* preform shutdown */
    env_cleanup( env );
    rand_clean_up();

    return 0;
}