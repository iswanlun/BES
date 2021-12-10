#include "brain.h"
#include "neurons.h"

/* Convert last 16 bits of gene to small (5,-5) 32 bit 
 * IEEE 754 float stored in a uint32 _t */
#define WEIGHT(x) ( (uint32_t) ( ( (x & 0x8000) << 16 ) | \
                    ( ( (0x81 - ( (x >> 13) & 0x3)) << 23) ) | \
                    ( (x & 0x1FFF) << 10) ) )

void wipe_buffers( brain* br ) {
    for ( int i = 0; i < COGNITION_COUNT; ++i ) {
        br->cognition_input[i] = 0;
    }
    for ( int i = 0; i < MOTOR_COUNT; ++i ) {
        br->motor_input[i] = 0;
    }
}

void fire_sense_neurons( brain* br, environment* env ) {

    for ( int i = 0; i < br->sense_len; ++i ) {

        uint32_t g = br->sense_n[i];

        uint8_t in = IN(g);
        uint8_t out = OUT(g);
        uint32_t weight = WEIGHT(g);
        float* w = (float*) &weight;
        
        if ( OUT_SRC(g) ) {
            br->motor_input[ out ] += ( *w * neuron_sense( env, br, in ) );
        } else {
            br->cognition_input[ out ] += ( *w * neuron_sense( env, br, in ) );
        }
    }
}

void warm_cognition_neurons( brain* br ) {

    for ( int i = 0; i < br->cognition_len; ++i ) {

        uint32_t g = br->cognition_n[i];
        
        if ( !OUT_SRC(g) ) {
        
            uint8_t in = IN(g);
            uint8_t out = OUT(g);
            uint32_t weight = WEIGHT(g);
            float* w = (float*) &weight;

            br->cognition_input[ out ] += ( *w * neuron_cognition( in, br->cognition_input[ in ] ) );
        }   
    }
}

void fire_cognition_neurons( brain* br ) {

    for ( int i = 0; i < br->cognition_len; ++i ) {

        uint32_t g = br->cognition_n[i];
        
        if ( OUT_SRC(g) ) {
        
            uint8_t in = IN(g);
            uint8_t out = OUT(g);
            uint32_t weight = WEIGHT(g);
            float* w = (float*) &weight;

            br->motor_input[ out ] += ( *w * neuron_cognition( in, br->cognition_input[ in ] ) );
        }   
    }
}

void fire_motor_neurons( brain* br, environment* env ) {

    for ( int i = 0; i < MOTOR_COUNT; ++i ) {

        if ( br->motor_input != 0 ) {
            neuron_motor( env, br, i, br->motor_input[ i ] );
        }
    }
}

void brain_react( brain* br, environment* env ) {

    /* Clean old data out */
    wipe_buffers( br );

    /* fire sense neurons */
    fire_sense_neurons(br, env);

    /* warm then fire cognition neurons */
    warm_cognition_neurons(br);
    fire_cognition_neurons(br);

    /* fire motor neurons */
    fire_motor_neurons(br, env);
}