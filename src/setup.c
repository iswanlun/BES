#include <unistd.h>
#include "setup.h"
#include "conf.h"
#include "graphics.h"
#include "log.h"

config_main main_cfg;
config_select select_cfg;

int setup_init( char* config_ini ) {

    if ( access( config_ini, R_OK ) ) {
        return 1;
    }

    conf_init( config_ini );

    char* graphics_path = conf_string("paths", "graphics");
    char* log_path = conf_string("paths", "log");

    if ( log_init( log_path ) | graphics_init( graphics_path ) ) {
        return 1;
    }

    main_cfg.generations = conf_int("main", "generations");
    main_cfg.iterations = conf_int("main", "iterations");
    main_cfg.x_dim = conf_int("main", "x_dim");
    main_cfg.y_dim = conf_int("main", "y_dim");
    main_cfg.population =  conf_int("main", "population");
    main_cfg.genome_size = conf_int("main", "genome_size");
    main_cfg.selector_type = conf_int("main", "selector_type");

    select_cfg.radiation_max = conf_float("selector","radiation_max");
    select_cfg.light_min = conf_float("selector","light_min");
    select_cfg.temp_min = conf_float("selector","temp_min");
    select_cfg.temp_max = conf_float("selector","temp_max");

    return 0;
}