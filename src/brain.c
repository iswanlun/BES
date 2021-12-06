#include "brain.h"
#include "neurons.h"

void wipe_sense_buffer( brain* br );
void wipe_cognition_buffer( brain* br );
void wipe_motor_buffer( brain* br );

/* Cognition neurons are allowed to form connections between each
 * other and to form circular connections. Warming these neurons
 * allows lateral signaling befor they are fired towards motor
 * neurons */
void warm_cognition_neurons( brain* br );

void fire_cognition_neurons( brain* br ) {

    for ( int i = 0; i < br->cognition_len; ++i ) {

        int32_t v = br->cognition_n[i];

        int8_t in = v >> 24;
        int8_t out = v >> 16;
        int8_t weight = ( v & 0xFF );

        if ( (out >> 6) == 0x2 ) {

            br->motor_input[ out & 0x3F ] += ( weight * neuron_cognition( br->cognition_input[ in ] ) );

        }
    }


}

void fire_sense_neurons( brain* br, environment* env );
void fire_motor_neurons( brain* br, environment* env );

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