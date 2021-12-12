#include <math.h>
#include <stddef.h>
#include "selector.h"
#include "log.h"
#include "rand.h"

#include <stdio.h>

#define RADIATION_MAX  -0.2
#define LIGHT_MIN       0.5
#define TEMP_MIN       -0.3
#define TEMP_MAX        0.25
#define ABS_MIN        -2.0
#define ABS_MAX         2.0
#define RAD             57.295

void eval_select_field( environment* env, size_t val, float min, float max ) {

    for ( int x = 0; x < env->x_dim; ++x ) {
        for ( int y = 0; y < env->y_dim; ++y ) {

            sector* sect = &env->grid[x][y];
            float f = *( (float*) &(((char*)sect)[val]) );

            sect->survive = (f >= min && f < max) ? 1:0;
        }
    }
}

void eval_select_limit( environment* env, int x_min, int y_min, int x_max, int y_max ) {
    
    for ( int x = 0; x < env->x_dim; ++x ) {
        for ( int y = 0; y < env->y_dim; ++y ) {

            env->grid[x][y].survive = ( x >= x_min && x < x_max && 
                                        y >= y_min && y < y_max );
        }
    }
}

int vec_field( int x, int y, int px, int py ) {

    float vx = (px - x) ? (px - x) : 1.0; /* no zeros */
    float vy = py - y;

    if ( vx > 0 ) {
        return 90 - (atan( vy / vx ) * RAD);
    }
    return 270 - (atan( vy / vx ) * RAD);
}

float prox( int x, int y, int px, int py, int max_x, int max_y ) {

    int vx = px - x;
    int vy = py - y;

    float lim_v = sqrtf((max_x * max_x) + (max_y * max_y)) / 2.0;
    float act_v = sqrtf((vx * vx) + (vy * vy));

    float dst_u = act_v / lim_v; 
    float dst_v = (dst_u > 1) ? 1:dst_u; 
    
    return 1.0 - (dst_v * 2.0);
}

void apply_source_field( environment* env, size_t val_off, size_t vec_off ) {

    int px = rand_next(0) % env->x_dim;
    int py = rand_next(0) % env->y_dim;

    char msg[40];
    sprintf( msg, "[field point applied] px: %i py: %i", px, py );
    log_msg( msg );

    for ( int x = 0; x < env->x_dim; ++x ) {
        for ( int y = 0; y < env->y_dim; ++y ) {
            
            *( (int*)   &(((char*)(&env->grid[x][y]))[vec_off]) ) = vec_field( x, y, px, py );
            *( (float*) &(((char*)(&env->grid[x][y]))[val_off]) ) = prox( x, y, px, py, env->x_dim, env->y_dim );
        }
    }
}

void selector_init( environment* env, int type ) {

    size_t val;
    int min, max;

    switch ( type ) {
        case( 0 ):      /* go north */
            eval_select_limit( env, 0, 0, env->x_dim, (env->y_dim / 2) );
            break;

        case( 1 ):      /* go east */
            eval_select_limit( env, (env->x_dim / 2), 0, env->x_dim, env->y_dim );
            break;

        case( 2 ):      /* go towards the light */
            apply_source_field( env, offsetof(sector, light), offsetof(sector, light_vector) );
            eval_select_field( env, offsetof(sector, light), LIGHT_MIN, ABS_MAX );
            break;

        case( 3 ):      /* stay away from radiation */
            apply_source_field( env, offsetof(sector, radiation), offsetof(sector, radiation_vector) );
            eval_select_field( env, offsetof(sector, radiation), ABS_MIN, RADIATION_MAX );
            break;

        case( 4 ):      /* find the warm zone */
            apply_source_field( env, offsetof(sector, temp), offsetof(sector, temp_vector) );
            eval_select_field( env, offsetof(sector, temp), TEMP_MIN, TEMP_MAX );
            break;
    }
}

void selector_update( environment* env, int type ) {

    if ( type > 1 ) {
        selector_init( env, type );
    }
}