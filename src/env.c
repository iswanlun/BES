#include <stdlib.h>
#include "env.h"
#include "spawn.h"
#include "rand.h"
#include "brain.h"

void env_disperse( environment* env ) {

    /* TODO: Randomly distribute brains in brain list into grid */

    for (int i = 0; i < env->population; ++i ) {

        uint32_t xy = rand_next( 1 );
        uint16_t x = ( ( xy >> 16 ) % env->x_dim );
        uint16_t y = ( ( xy & 0xFFFF ) % env->y_dim );
        env->brains[i]->dir = ( xy % 4 ) * 90;

        while ( env->grid[x][y].occupant != NULL ) {
            x = ( (x + 2) % env->x_dim );
            y = ( (y + 1) % env->y_dim );
        }

        env->brains[i]->x_pos = x;
        env->brains[i]->y_pos = y;
        env->grid[x][y].occupant = env->brains[i];
    }
}

environment* env_new( int x_dim, int y_dim ) {

    environment* env = (environment*) calloc( 1, sizeof(environment) );
    env->x_dim = x_dim;
    env->y_dim = y_dim;
    env->osc = 0;

    env->grid = (sector**) calloc( x_dim, sizeof(sector*) );

    for ( int x = 0; x < x_dim; ++x ) {
        env->grid[x] = (sector*) calloc( y_dim, sizeof(sector) );
    }
    
    return env;
}

void env_populate( environment* env, int pop, int genome_size ) {

    env->population = pop;
    env->brains = (brain**) calloc( pop, sizeof(brain*) );

    for( int i = 0; i < pop; ++i ) {

        env->brains[i] = spawn_new( genome_size );
    }

    env_disperse( env );
}

void env_select( environment* env, char (*select)(int, int) ) {
    
    for ( int x = 0; x < env->x_dim; ++x ) {
        for ( int y = 0; y < env->y_dim; ++y ) {
            env->grid[x][y].survive = select(x,y);
        }
    }
}

/* Differs from select in that select applies a sections criteria to individual
 * sectors, where as cull removes brains in non-surviving sectors. 
 * Culling removes brains from memory. */
int env_cull( environment* env ) {

    for ( int i = 0; i < env->population; ++i ) {
        env->brains[i] = NULL; /* clear brains list to prevent dangling refrences */
    }
    
    int survivors = 0;

    for ( int x = 0; x < env->x_dim; ++x ) {
        for ( int y = 0; y < env->y_dim; ++y ) {

            if ( env->grid[x][y].survive ) {
                survivors++;
            } else {
                spawn_remove( env->grid[x][y].occupant );
                env->grid[x][y].occupant = NULL;
            }
        }
    }
    return survivors;
}

/* Repopulate an environment after culling */
void env_regenerate( environment* env ) {

    /* calculate the number to create per survivor */
    int per_parent = ( env->population / env_cull( env ) );
    int pop_index = 0, secondary = 0;

    for ( int x = 0; x < env->x_dim; ++x ) {
        for ( int y = 0; y < env->y_dim; ++y ) {
            
            if ( env->grid[x][y].occupant != NULL ) {

                if ( pop_index + per_parent > env->population ) {
                    per_parent = env->population - pop_index;
                }

                for ( int i = 0; i < per_parent; ++i ) {
                    env->brains[pop_index++] = spawn_breed( env->grid[x][y].occupant );
                }

                spawn_remove( env->grid[x][y].occupant );
                env->grid[x][y].occupant = NULL;
            }
        }
    }

    while ( pop_index < env->population ) {
        env->brains[pop_index++] = spawn_breed( env->brains[secondary++] );
    }

    env_disperse( env );
}

/* Runs the selected number of iterations constituting a single generation
 * or sub generation */
void env_run_iterations( environment* env, int iters ) {

    for ( int i = 0; i < iters; ++i ) {
        for ( int b = 0; b < env->population; ++b ) {
            brain_react( env->brains[b], env );
        }
        env->osc += 0.5; /* advance oscillator */
    }
}

/* Free env and brain resources */
void env_cleanup( environment* env ) {

    for ( int i = 0; i < env->population; ++i ) {
        spawn_remove( env->brains[i] );
        env->brains[i] = NULL;
    }
    free( env->brains );

    for ( int x = 0; x < env->x_dim; ++x ) {
        free( env->grid[x] );
    }
    free( env->grid );
}