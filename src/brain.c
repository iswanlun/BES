#include "brain.h"
#include "neurons.h"

#define IN(x)       ( ( x >> 24 ) & 0x7F )      /* The neuron and buffer to draw from */
#define OUT(x)      ( ( x >> 16 ) & 0x7F )      /* The neuron and buffer to place results into */

/* Convert last 16 bits of gene to small (5,-5) 32 bit IEEE 754 float stored in an int */
#define WEIGHT(x)   ( (int32_t) ( ( (x & 0x8000) << 16 ) | ( ( (0x81 - ( (x >> 13) & 0x3)) << 23) ) | ( (x & 0x1FFF) << 10) ) )

#define IN_DEST(x)  ( ( x >> 31 ) & 0x1 )
#define OUT_DEST(x) ( ( x >> 23 ) & 0x1 )

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
        int32_t weight = WEIGHT(g);
        float* w = &weight;
        
        if ( OUT_DEST(g) ) {
            br->motor_input[ out ] += ( *w * neuron_sense( env, br, in ) );
        } else {
            br->cognition_input[ out ] += ( *w * neuron_sense( env, br, in ) );
        }
    }
}

void warm_cognition_neurons( brain* br ) {

    for ( int i = 0; i < br->cognition_len; ++i ) {

        int16_t g = br->cognition_n[i];
        
        if ( !OUT_DEST(g) ) {
        
            int8_t in = IN(g);
            int8_t out = OUT(g);
            int32_t weight = WEIGHT(g);
            float* w = &weight;

            br->cognition_input[ out ] += ( *w * neuron_cognition( in, br->cognition_input[ in ] ) );
        }   
    }
}

void fire_cognition_neurons( brain* br ) {

    for ( int i = 0; i < br->cognition_len; ++i ) {

        int16_t g = br->cognition_n[i];
        
        if ( OUT_DEST(g) ) {
        
            int8_t in = IN(g);
            int8_t out = OUT(g);
            int32_t weight = WEIGHT(g);
            float* w = &weight;

            br->motor_input[ out ] += ( *w * neuron_cognition( in, br->cognition_input[ in ] ) );
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