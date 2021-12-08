
#include <stdlib.h>
#include "neurons.h"
#include "math.h"
/* Floating point numbers are expensive: Neuton outputs should be between 0 and 1000 */

/* sense neurons */
float north_south( brain* br ) {
    
    switch ( br->dir ) {
        case( 0   ): return  1;
        case( 180 ): return -1;
    }
    return 0;
}

float east_west( brain* br ) {

    switch ( br->dir ) {
        case( 90  ): return  1;
        case( 270 ): return -1;
    }
    return 0;
}

float vec_diff( int from, int to ) {

    int diff = to - from;
    
    if ( diff > 180 ){
        diff = (diff - 360) * -1;
    } else if ( diff < -180 ) {
        diff += 360;
    }
    return diff / 180;
}

float light_dark( environment* env, brain* br ) {
    return vec_diff( br->dir, env->grid[br->x_pos][br->y_pos].light_vector );
}

float brightness( environment* env, brain* br ) {
    return env->grid[br->x_pos][br->y_pos].light;
}

float cold_warm( environment* env, brain* br ) {
    return vec_diff( br->dir, env->grid[br->x_pos][br->y_pos].temp_vector );
}

float temp( environment* env, brain* br ) {
    return env->grid[br->x_pos][br->y_pos].temp;
}

float radiation_vector( environment* env, brain* br ) {
    return vec_diff( br->dir, env->grid[br->x_pos][br->y_pos].radiation_vector );
}

float radiation( environment* env, brain* br ) {
    return env->grid[br->x_pos][br->y_pos].radiation;
}

float slow_oscillator( environment* env ) {
    return sinf( 0.3 * env->osc );
}

float fast_oscillator( environment* env ) {
    return sinf( env->osc );
}

/* cognition neurons */
float small_neuron( float input ) {

    return tanhf( 0.9 * input );
}

float medium_neuron( float input ) {

    return tanhf( input );
}

float large_neuron( float input ) {

    return tanhf( 1.1 * input );
}

// TODO : REWORK THIS TO ALSO MOVE IN THE DIRECTION 
void move_in_direction( environment* env, brain* br, int dir ) {

    int x = 0, y = 0;

    switch( dir ) {
        case( 0 ):      if ( br->y_pos < (env->y_dim-1) ) { y = 1; }
                        break;

        case( 90 ):     if ( br->x_pos < (env->x_dim-1) ) { x = 1; }
                        break;

        case( 180 ):    if ( br->y_pos > 0 ) { y = -1; }
                        break;

        case( 270 ):    if ( br->x_pos > 0 ) { x = -1; }
                        break;
    }

    if ( x | y ) {
        
        sector* sec = &(env->grid[br->x_pos + x][br->y_pos + y]);

        if ( sec->occupant != NULL ) {

            sec->occupant = br; /* claim the new sector */
            env->grid[br->x_pos][br->y_pos].occupant = NULL; /* release the old sector */
            
            br->x_pos += x; /* update brain coordinates */
            br->y_pos += y;
        }
    }
}

/* motor neurons */
void move_forward_back( environment* env, brain* br, float input ) {

    float norm = tanhf( input );

    if ( norm > FB_DRIVE ) {
        move_in_direction( env, br, br->dir );
        
    } else if ( norm < -FB_DRIVE ) {
        move_in_direction( env, br, ((br->dir + 180) % 360) );
    }
}

void move_right_left( environment* env, brain* br, int input ) {

}
void move_random( environment* env, brain* br, int input ) {}
void move_rotate( brain* br, int imput );

/* Get the value of the specified sense neuron */
float neuron_sense( environment* env, brain* br, int8_t gene_index ) {

    switch( gene_index ) {
        case( 0x0 ): return north_south( br );
        case( 0x1 ): return east_west( br );
        case( 0x2 ): return light_dark( env, br );
        case( 0x3 ): return brightness( env, br );
        case( 0x4 ): return cold_warm( env, br );
        case( 0x5 ): return temp( env, br );
        case( 0x6 ): return radiation( env, br );
        case( 0x7 ): return radiation_vector( env, br );
        case( 0x8 ): return slow_oscillator( env );
        case( 0x9 ): return fast_oscillator( env );
    }
    return 0;
}

/* Get the value of the specified cognitive neuron given an input parameter */
float neuron_cognition( int8_t gene_index, float input ) {

    switch( gene_index ) {
        case( 0x0 ): return small_neuron( input );
        case( 0x1 ): return medium_neuron( input );
        case( 0x2 ): return large_neuron( input );
    }
    return 0;
}

/* Active the specified motor neuron */
void neuron_motor( environment* env, brain* br, int8_t gene_index, int input ) {

    switch( gene_index ) {
        case( 0x0 ): return move_forward_back( env, br, input );
        case( 0x1 ): return move_right_left( env, br, input );
        case( 0x2 ): return move_random( env, br, input );
    }
    return 0;
}