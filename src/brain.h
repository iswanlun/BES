#ifndef BRAIN_H
#define BRAIN_H

#include <stdint.h>
#include "neurons.h"
#include "env.h"

#define IN(x)       ( ( x >> 24 ) & 0x7F )      /* Input neuron index and buffer */
#define OUT(x)      ( ( x >> 16 ) & 0x7F )      /* Output neuron index and buffe */
#define IN_SRC(x)   ( ( x >> 31 ) & 0x1  )      /* Input source */
#define OUT_SRC(x)  ( ( x >> 23 ) & 0x1  )      /* Output source */

typedef struct {

    /* internal brain buffers */
    float sense_input[SENSE_COUNT];
    float cognition_input[COGNITION_COUNT];
    float motor_input[MOTOR_COUNT];

    uint32_t* raw_genome; /* Raw genome with full variations */
    int raw_genome_len;

    uint32_t* sense_n;       /* Genome, sense neuron pathways */
    int sense_len;

    uint32_t* cognition_n;   /* Genome, cognition neuron pathways */
    int cognition_len;

    /* world realitive data */
    int x_pos;
    int y_pos;
    
    /* direction, degrees */
    int dir;

} brain;

void brain_react( brain* br, environment* env );

#endif