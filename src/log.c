
#include <stdio.h>
#include <unistd.h>
#include "log.h"

static const char* log;

int log_init( const char* log_path ) {

    log = log_path;
    return access( log, ( R_OK | W_OK ) );
}

void log_itteration( environment* env ) {

    printf( "singled iter.\n" );
}

void log_generation( environment* env, int survivors ) {

    printf(" Generation %d stats: ", env->gen );
    printf(" \tSurvivors: %d \n", survivors );
}