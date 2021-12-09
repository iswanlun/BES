
#include <stdio.h>
#include <unistd.h>
#include "log.h"

#define DEBUG 1

static const char* log;

int log_init( const char* log_path ) {

    log = log_path;
    return access( log, ( R_OK | W_OK ) );
}

void log_itteration( environment* env ) {

    FILE* fp = fopen( log, "a" );
    fprintf( fp, "Single iter.\n" );
    fclose( fp );
}

void log_generation( environment* env, int survivors ) {

    FILE* fp = fopen( log, "a" );
    fprintf( fp, " Generation %d stats: ", env->gen );
    fprintf( fp, " \tSurvivors: %d \n", survivors );
    fclose( fp );
}

void log_sim_issue( const char* err ) {
    FILE* fp = fopen( log, "a" );
    fprintf( fp, "%s\n", err );
    fclose( fp );
}

void log_msg( const char* msg ) {
#ifdef DEBUG
    log_sim_issue( msg );
#endif
}