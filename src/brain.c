#include "brain.h"
#include "neurons.h"

#define IN(x)       ( ( x >> 10) & 0x1F )
#define OUT(x)      ( ( x >> 4 ) & 0x1F )
#define WEIGHT(x)   ( (int8_t) (((x & 0x8) << 4) | (x & 0x7)) )

#define IN_DEST(x)  ( x >> 15 )
#define OUT_DEST(x) ( (x >> 9 ) & 0x1 )

void wipe_sense_buffer( brain* br );
void wipe_cognition_buffer( brain* br );
void wipe_motor_buffer( brain* br );

/* Cognition neurons are allowed to form connections between each
 * other and to form circular connections. Warming these neurons
 * allows lateral signaling befor they are fired towards motor
 * neurons */


void fire_sense_neurons( brain* br, environment* env ) {

    for ( int i = 0; i < br->sense_len; ++i ) {

        int16_t g = br->sense_n[i];


    }

}

void warm_cognition_neurons( brain* br ) {

    for ( int i = 0; i < br->cognition_len; ++i ) {

        int16_t g = br->cognition_n[i];
        
        if ( !OUT_DEST(g) ) {
        
            int8_t in = IN(g) % COGNITION_COUNT;
            int8_t out = OUT(g) % COGNITION_COUNT;
            int8_t weight = WEIGHT(g);

            br->cognition_input[ out ] += ( weight * neuron_cognition( br->cognition_input[ in ] ) );
        }   
    }
}

void fire_cognition_neurons( brain* br ) {

    for ( int i = 0; i < br->cognition_len; ++i ) {

        int16_t g = br->cognition_n[i];
        
        if ( OUT_DEST(g) ) {
        
            int8_t in = IN(g) % COGNITION_COUNT;
            int8_t out = OUT(g) % MOTOR_COUNT;
            int8_t weight = WEIGHT(g);

            br->motor_input[ out ] += ( weight * neuron_cognition( br->cognition_input[ in ] ) );
        }   
    }
}

void fire_motor_neurons( brain* br, environment* env ) {

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