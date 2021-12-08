#include "neurons.h"
#include "math.h"
/* Floating point numbers are expensive: Neuton outputs should be between 0 and 1000 */

/* sense neurons */
signed char north_south( environment* env, brain* br ) {
    
    switch ( br->dir ) {
        case( 0   ): return  1;
        case( 180 ): return -1;
    }
    return 0;
}

signed char east_west( environment* env, brain* br ) {

    switch ( br->dir ) {
        case( 90  ): return  1;
        case( 270 ): return -1;
    }
    return 0;
}
signed char light_dark( environment* env, brain* br ) {

    /* detirmine the difference between brain direction and light source */

    int diff = env->grid[br->x_pos][br->y_pos].light_vector - br->dir;
    
    if ( diff > 180 ){
        diff = (diff - 360) * -1;
    } else if ( diff < -180 ) {
        diff += 360;
    }

    return diff / 180;
}

signed char brightness( environment* env, brain* br ) {

    return env->grid[br->x_pos][br->y_pos].light;
}

signed char cold_warm( environment* env, brain* br ) {}
signed char temp( environment* env, brain* br ) {}
signed char radiation( environment* env, brain* br ) {}
signed char oscillator( void ) {}

/* cognition neurons */
signed char small_neuron( int input ) {}
signed char medium_neuron( int input ) {}
signed char large_neuron( int input ) {}

/* motor neurons */
void move_forward_back( environment* env, brain* br, int input ) {}
void move_right_left( environment* env, brain* br, int input ) {}
void move_random( environment* env, brain* br, int input ) {}
void move_rotate( brain* br, int imput );

/* Get the value of the specified sense neuron */
signed char neuron_sense( environment* env, brain* br, int8_t gene_index ) {

    switch( gene_index ) {
        case( 0x0 ): return north_south( env, br );
        case( 0x1 ): return east_west( env, br );
        case( 0x2 ): return light_dark( env, br );
        case( 0x3 ): return cold_warm( env, br );
        case( 0x4 ): return radiation( env, br );
        case( 0x5 ): return oscillator();
    }
    return 0;
}

/* Get the value of the specified cognitive neuron given an input parameter */
signed char neuron_cognition( int8_t gene_index, int input ) {

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