#ifndef NEURONS_H
#define NEURONS_H

#include "env.h"
#include "brain.h"
#include <stdint.h>

#define SENSE_COUNT 3
#define COGNITION_COUNT 3
#define MOTOR_COUNT 3

/* Get the value of the specified sense neuron */
unsigned int neuron_sense( environment* env, brain* br, int8_t gene_index );

/* Get the value of the specified cognitive neuron given an input parameter */
unsigned int neuron_cognition( int8_t gene_index, int input );

/* Active the specified motor neuron */
void neuron_motor( environment* env, brain* br, int8_t gene_index, int input );

#endif
