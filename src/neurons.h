#ifndef NEURONS_H
#define NEURONS_H

#include "env.h"
#include <stdint.h>

#define SENSE_COUNT 3
#define COGNITION_COUNT 3
#define MOTOR_COUNT 3

/* sensory neurons */

unsigned char north_south( environment* env );
unsigned char east_west( environment* env );
unsigned char light_dark( environment* env );
unsigned char cold_warm( environment* env );


/* cognitive neurons */

unsigned char neuron_cognition( signed char input );

/* motor neurons */

#endif
