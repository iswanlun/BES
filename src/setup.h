#ifndef SETUP_H
#define SETUP_H

typedef struct _config_main {

    int generations, 
    iterations, 
    x_dim, 
    y_dim, 
    population, 
    genome_size,
    selector_type;

} config_main;

typedef struct _config_select {

    float radiation_max,
    light_min,
    temp_min,
    temp_max;

} config_select;

extern config_main main_cfg;
extern config_select select_cfg;

int setup_init( char* config );

void setup_teardown( void );

#endif