#ifndef BRAIN_H
#define BRAIN_H

#include <stdint.h>
#include "neurons.h"
#include "env.h"

typedef struct {

    /* internal brain buffers */
    float sense_input[SENSE_COUNT];
    float cognition_input[COGNITION_COUNT];
    float motor_input[MOTOR_COUNT];

    int32_t* raw_genome; /* Raw genome with full variations */
    int raw_genome_length;

    int32_t* sense_n;       /* Genome, sense neuron pathways */
    int sense_len;

    int32_t* cognition_n;   /* Genome, cognition neuron pathways */
    int cognition_len;

    int32_t* motor_n;       /* Genome, active motor neurons */
    int motor_len;

    /* world realitive data */
    int x_pos;
    int y_pos;
    
    /* direction, degrees */
    int dir;

} brain;

void brain_react( brain* br, environment* env );

#endif