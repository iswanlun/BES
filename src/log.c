#include <stdio.h>
#include <unistd.h>
#include "log.h"

static FILE* log_fp;

int log_init( const char* log_path ) {

    if ( access(log_path, ( R_OK | W_OK )) )  {
        return 1;
    }
    log_fp = fopen( log_path, "a" );
    return 0;
}

void log_itteration( environment* env ) {

    fprintf( log_fp, "[Itteration]\n" );
}

void log_generation( environment* env, int survivors ) {

    fprintf( log_fp, "Generation %d stats: \n", env->gen );
    fprintf( log_fp, "\tSurvivors: %d \n", survivors );
}

void log_msg( const char* msg ) {

    fprintf( log_fp, "%s\n", msg );
}

void log_teardown( void ) {
    fclose( log_fp );
}