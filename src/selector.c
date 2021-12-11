#include <math.h>
#include <stddef.h>
#include "selector.h"
#include "rand.h"

#define RADIATION_MAX   0.3
#define LIGHT_MIN       0.5
#define TEMP_MIN       -0.3
#define TEMP_MAX        0.6
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

    int vx = (px - x) ? (px - x) : 1; /* no zeros */
    int vy = py - y;

    if ( vx > 0 ) {
        return 90 - (atan( vy / vx ) * RAD);
    }
    return 270 - (atan( vy / vx ) * RAD);
}

float prox( int x, int y, int px, int py, int max_x, int max_y ) {

    int vx = px - x;
    int vy = py - y;
    float max_v = sqrtf( pow(max_x, 2) + pow(max_y, 2) );
    float act_v = sqrtf( pow(vx, 2) + pow(vy, 2) );

    return 1.0 - ((act_v / max_v ) * 2.0);
}

void apply_source_field( environment* env, size_t val_off, size_t vec_off ) {

    int px = rand_next(0) % env->x_dim;
    int py = rand_next(0) % env->y_dim;

    for ( int x = 0; x < env->x_dim; ++x ) {
        for ( int y = 0; y < env->y_dim; ++y ) {
            
            *( (int*)   &(((char*)(&env->grid[x][y]))[vec_off]) ) = vec_field( x, y, px, py );
            *( (float*) &(((char*)(&env->grid[x][y]))[val_off]) ) = prox( x, y, px, py, env->x_dim, env->y_dim );

            int f = *( (int*)   &(((char*)(&env->grid[x][y]))[vec_off]) );
            float m = *( (float*) &(((char*)(&env->grid[x][y]))[val_off]) );

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
            eval_select_field( env, offsetof(sector, light), LIGHT_MIN, 2 );
            break;

        case( 3 ):      /* stay away from radiation */
            apply_source_field( env, offsetof(sector, radiation), offsetof(sector, radiation_vector) );
            eval_select_field( env, offsetof(sector, radiation), 0, RADIATION_MAX );
            break;

        case( 4 ):      /* find the warm temp zone */
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