#ifndef ENV_H
#define ENV_H

#include <stdint.h>

#define SENSE_COUNT 11
#define COGNITION_COUNT 3
#define MOTOR_COUNT 4

typedef struct _brain {

    /* internal brain buffers */
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

    /* color code */
    int color;

} brain;

/* A sector is a single space in the environment which a single brain may occupy */
typedef struct _sector {

    brain* occupant; /* occupant */

    /* sector data */
    char survive; /* sector selection criteria bool ( 0, 1 ) */

    float temp; /* -1 - 0 */
    int temp_vector; /* direction of heat source, degrees */

    float light; /* -1 - 0 */
    int light_vector; /* direction of light source, degrees */

    float radiation; /* -1 - 0 */
    int radiation_vector; /* direction of radiation source */

} sector;

typedef struct _environment {

    /* 2d world grid */
    sector** grid;
    int x_dim;
    int y_dim;

    /* list of all brains in env */
    brain** brains;

    /* population */
    int population;

    /* oscillator */
    float osc;

    /* generation counter */
    int gen;

} environment;

/* create a new environment */
environment* env_new( int x_dim, int y_dim );

/* populate the environment initally with new brains created at random
 * and disperse them throughout the env randomly */
void env_populate( environment* env, int pop, int genome_size );

/* Differs from select in that select applies a sections criteria to individual
 * sectors, where as cull removes brains in non-surviving sectors. 
 * Culling removes brains from memory. Returns the number of survivors. */
int env_cull( environment* env );

/* Repopulate an environment after culling */
void env_regenerate( environment* env );

/* Runs the selected number of iterations constituting a single generation
 * or sub generation */
void env_run_generation( environment* env, int iters );

/* Free env and brain resources */
void env_cleanup( environment* env );

#endif