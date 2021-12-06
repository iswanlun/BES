#include "brain.h"
#include "neurons.h"

#define IN(x)       ( ( x >> 10 ) & 0x1F )      /* The neuron and buffer to draw from */
#define OUT(x)      ( ( x >> 4  ) & 0x1F )      /* The neuron and buffer to place results into */
#define WEIGHT(x)   ( ((int8_t)(x & 0xF)) - 8 ) /* Subtract 8 to yield negative number */

#define IN_DEST(x)  ( ( x >> 15 ) & 0x1 )
#define OUT_DEST(x) ( ( x >> 9  ) & 0x1 )

void wipe_buffers( brain* br ) {
    for ( int i = 0; i < SENSE_COUNT; ++i ) {
        br->sense_input[i] = 0;
    }
    for ( int i = 0; i < COGNITION_COUNT; ++i ) {
        br->cognition_input[i] = 0;
    }
    for ( int i = 0; i < MOTOR_COUNT; ++i ) {
        br->motor_input[i] = 0;
    }
}

void fire_sense_neurons( brain* br, environment* env ) {

    for ( int i = 0; i < br->sense_len; ++i ) {

        int16_t g = br->sense_n[i];

        int8_t in = IN(g);
        int8_t out = OUT(g);
        int8_t weight = WEIGHT(g);

        br->cognition_input[ out ] += ( weight * neuron_sense( env, br, in ) );
    }
}

void warm_cognition_neurons( brain* br ) {

    for ( int i = 0; i < br->cognition_len; ++i ) {

        int16_t g = br->cognition_n[i];
        
        if ( !OUT_DEST(g) ) {
        
            int8_t in = IN(g);
            int8_t out = OUT(g);
            int8_t weight = WEIGHT(g);

            br->cognition_input[ out ] += ( weight * neuron_cognition( in, br->cognition_input[ in ] ) );
        }   
    }
}

void fire_cognition_neurons( brain* br ) {

    for ( int i = 0; i < br->cognition_len; ++i ) {

        int16_t g = br->cognition_n[i];
        
        if ( OUT_DEST(g) ) {
        
            int8_t in = IN(g);
            int8_t out = OUT(g);
            int8_t weight = WEIGHT(g);

            br->motor_input[ out ] += ( weight * neuron_cognition( in, br->cognition_input[ in ] ) );
        }   
    }
}

void fire_motor_neurons( brain* br, environment* env ) {

    for ( int i = 0; i < br->motor_len; ++i ) {

        int16_t g = br->motor_n[i];
        int8_t out = OUT(g);

        neuron_motor( env, br, out, br->motor_input[ out ] );
    }
}

void brain_react( brain* br, environment* env ) {

    /* Clean old data out */
    wipe_sense_buffer(br);
    wipe_cognition_buffer(br);
    wipe_motor_buffer(br);

    /* fire sense neurons */
    fire_sense_neurons(br, env);

    /* warm then fire cognition neurons */
    warm_cognition_neurons(br);
    fire_cognition_neurons(br);

    /* fire motor neurons */
    fire_motor_neurons(br, env);
}