#ifndef BRAIN_H
#define BRAIN_H

#include <stdint.h>
#include "neurons.h"
#include "env.h"

typedef struct {

    /* internal brain buffers */
    int sense_input[SENSE_COUNT];
    int cognition_input[COGNITION_COUNT];
    int motor_input[MOTOR_COUNT];

    int32_t* sense_n;       /* Genome, sense neuron pathways */
    int sense_len;

    int32_t* cognition_n;   /* Genome, cognition neuron pathways */
    int cognition_len;

    /* world realitive data */
    int x_pos;
    int y_pos;
    // direction brain points in ( N-S-E-W )
    // age, sex, etc (?)

} brain;

void brain_react( brain* br, environment* env );


#endif