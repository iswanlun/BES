#ifndef NEURONS_H
#define NEURONS_H

#include "env.h"
#include "brain.h"
#include <stdint.h>

#define SENSE_COUNT 10
#define COGNITION_COUNT 3
#define MOTOR_COUNT 4

#define FB_DRIVE 0.5
#define LR_DRIVE 0.7
#define RM_DRIVE 0.4
#define RT_DRIVE 0.6

/* Get the value of the specified sense neuron */
float neuron_sense( environment* env, brain* br, int8_t gene_index );

/* Get the value of the specified cognitive neuron given an input parameter */
float neuron_cognition( int8_t gene_index, float input );

/* Active the specified motor neuron */
void neuron_motor( environment* env, brain* br, int8_t gene_index, int input );

#endif
