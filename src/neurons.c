#include "neurons.h"

/* Floating point numbers are expensive: Neuton outputs should be between 0 and 1000 */

/* sense neurons */
unsigned int north_south( environment* env, brain* br ) {}
unsigned int east_west( environment* env, brain* br ) {}
unsigned int light_dark( environment* env, brain* br ) {}
unsigned int brightness( environment* env, brain* br ) {}
unsigned int cold_warm( environment* env, brain* br ) {}
unsigned int temp( environment* env, brain* br ) {}
unsigned int radiation( environment* env, brain* br ) {}
unsigned int oscillator( void ) {}

/* cognition neurons */
unsigned int small_neuron( int input ) {}
unsigned int medium_neuron( int input ) {}
unsigned int large_neuron( int input ) {}

/* motor neurons */
void move_forward_back( environment* env, brain* br, int input ) {}
void move_right_left( environment* env, brain* br, int input ) {}
void move_random( environment* env, brain* br, int input ) {}

/* Get the value of the specified sense neuron */
unsigned int neuron_sense( environment* env, brain* br, int8_t gene_index ) {

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
unsigned int neuron_cognition( int8_t gene_index, int input ) {

    switch( gene_index ) {
        case( 0x1 ): return small_neuron( input );
        case( 0x2 ): return medium_neuron( input );
        case( 0x3 ): return large_neuron( input );
    }
    return 0;
}

/* Active the specified motor neuron */
void neuron_motor( environment* env, brain* br, int8_t gene_index, int input ) {

    switch( gene_index ) {
        case( 0x1 ): return move_forward_back( env, br, input );
        case( 0x2 ): return move_right_left( env, br, input );
        case( 0x3 ): return move_random( env, br, input );
    }
    return 0;
}