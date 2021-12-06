#ifndef ENV_H
#define ENV_H

#include "brain.h"

/**
 * Env: Environment where brains will live.
 * Environment is a 2d grid divided into sectors where
 * each sector contains some world data and optionally
 */

/* A sector is a single space in the environment which a single brain may occupy */
typedef struct {

    brain* occupant; /* occupant */

    char survive; /* spatial selection criteria bool ( 0, 1 ) */

    // mutex

} sector;

typedef struct {

    /* 2d world grid */
    sector** env;

    int x_dim;
    int y_dim;

    /* list of all brains in env */
    brain* brains;

    /* population */
    int population;
    
    /* world data, might refactor to be in sectors */
    // temperature
    // lighting
    // radiation
    // food sources (?)

} environment;

/* create a new environment */
environment* env_new( int width, int length );

/* populate the environment initally with new brains created at random
 * and disperse them throughout the env randomly */
void env_populate( environment* env, int pop );

/* apply a selection criteria realitive to world,
 * pointer to fuction which takes in coordinates and returns true / false
 * if coord survives */
void env_select( environment* env, char (*select)(int, int) );

/* Differs from select in that select applies a sections criteria to individual
 * sectors, where as cull removes brains in non-surviving sectors. 
 * Culling removes brains from memory. */
void env_cull( environment* env );

/* Repopulate an environment after culling */
void env_regenerate( environment* env );

/* Runs the selected number of iterations constituting a single generation
 * or sub generation */
void env_run_iterations( environment* env, int iters );

#endif