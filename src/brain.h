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

    int16_t* sense_n;       /* Genome, sense neuron pathways */
    int sense_len;

    int16_t* cognition_n;   /* Genome, cognition neuron pathways */
    int cognition_len;

    int16_t* motor_n;       /* Genome, active motor neurons */
    int motor_len;

    /* world realitive data */
    int x_pos;
    int y_pos;
    
    /* direction */
    char dir;

} brain;

void brain_react( brain* br, environment* env );

#endif