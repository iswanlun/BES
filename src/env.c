#include <stdlib.h>
#include <math.h>
#include "env.h"
#include "spawn.h"
#include "rand.h"
#include "brain.h"
#include "log.h"
#include "string.h"
#include "graphics.h"

#define DEFAULT_GENOME 8

void env_disperse( environment* env ) {

    for (int i = 0; i < env->population; ++i ) {

        uint32_t xy = rand_next( 0 );
        uint16_t x = ( ( xy >> 16 ) % env->x_dim );
        uint16_t y = ( ( xy & 0xFFFF ) % env->y_dim );

        while ( env->grid[x][y].occupant != NULL ) {
            x = ( (x + 2) % env->x_dim );
            y = ( (y + 1) % env->y_dim );
        }

        env->brains[i]->dir = ( xy % 4 ) * 90;
        env->brains[i]->x_pos = x;
        env->brains[i]->y_pos = y;
        env->grid[x][y].occupant = env->brains[i];
    }
}

environment* env_new( int x_dim, int y_dim ) {

    environment* env = (environment*) malloc( sizeof(environment) );
    env->x_dim = x_dim;
    env->y_dim = y_dim;
    env->osc = 0;
    env->gen = 0;

    env->grid = (sector**) calloc( x_dim, sizeof(sector*) );

    for ( int x = 0; x < x_dim; ++x ) {
        env->grid[x] = (sector*) calloc( y_dim, sizeof(sector) );
    }
    
    return env;
}

void env_populate( environment* env, int pop, int genome_size ) {

    env->population = pop;
    env->brains = (brain**) malloc( pop * sizeof(brain*) );

    for( int i = 0; i < pop; ++i ) {
        env->brains[i] = spawn_new( genome_size );
    }

    env_disperse( env );
}

/* Differs from select in that select applies a sections criteria to individual
 * sectors, cull removes non surviving brains from memory. */
int env_cull( environment* env ) {

    int survivors = 0;

    for ( int i = 0; i < env->population; ++i ) {

        int x = env->brains[i]->x_pos;
        int y = env->brains[i]->y_pos;

        if ( env->grid[x][y].survive ) {
            survivors++;
        } else {
            spawn_remove( env->brains[i] );
            env->brains[i] = NULL; /* remove dangling refrence in array to non survivor */
        }

        env->grid[x][y].occupant = NULL; /* Remove all brains from occupied grid sectors */
    }

    return survivors;
}

/* Repopulate an environment after culling */
void env_regenerate( environment* env ) {

    int survivors = env_cull( env );
    log_generation( env, survivors );

    if ( 0 == survivors ) {
        
        log_msg( "Brain extinction: No survivors in generation." );
        
        for ( int i = 0; i < env->population; ++i ) {
            env->brains[i] = spawn_new( DEFAULT_GENOME );
        }

        env_disperse( env );
        env->gen++;
        return;
    }
    
    brain* next_gen[env->population];

    /* calculate the number to create per survivor */
    int next_index = 0, secondary = 0;
    int per_parent = ( env->population / survivors );

    for ( int i = 0; i < env->population; ++i ) {
           
        if ( env->brains[i] != NULL ) {

            if ( (next_index + per_parent) > env->population ) {
                per_parent = env->population - next_index;
            }

            for ( int p = 0; p < per_parent; ++p ) {
                next_gen[next_index++] = spawn_breed( env->brains[i] );
            }

            spawn_remove( env->brains[i] );
            env->brains[i] = NULL; /* remove dangling pointer in list */
        }
    }

    while ( next_index < env->population ) {
        next_gen[next_index++] = spawn_breed( next_gen[secondary++] );
    }

    memcpy( env->brains, next_gen, (env->population * sizeof(uint32_t*)) ); /* move values from stack to heap */
    env_disperse( env );
    env->gen++;
}

char env_graphic_gen( int gen ) {

    int r = (int)sqrt( gen );
    int t = (r * r);

    return (t == gen);
}

/* Runs the selected number of iterations constituting a single generation
 * or sub generation */
void env_run_generation( environment* env, int iters ) {

    if ( env_graphic_gen( env->gen ) ) {

        graphics_start_gif( env, "View" );
        graphics_add_frame( env );

        for ( int i = 0; i < iters; ++i ) {
            for ( int b = 0; b < env->population; ++b ) {
                brain_react( env->brains[b], env );
            }
            graphics_add_frame( env );
            env->osc += 0.5; /* advance oscillator */
        }
        graphics_generate_gif();

    } else {
        for ( int i = 0; i < iters; ++i ) {
            for ( int b = 0; b < env->population; ++b ) {
                brain_react( env->brains[b], env );
            }
            env->osc += 0.5; /* advance oscillator */
        }
    }
}

/* Free env and brain resources */
void env_teardown( environment* env ) {

    log_msg("[env_cleanup]");

    for ( int i = 0; i < env->population; ++i ) {
        spawn_remove( env->brains[i] );
        env->brains[i] = NULL;
    }
    free( env->brains );

    for ( int x = 0; x < env->x_dim; ++x ) {
        free( env->grid[x] );
    }
    free( env->grid );

    free( env );
}