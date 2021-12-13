#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "conf.h"

static FILE* conf_fp;

int conf_section( char* buf, const char* section ) {

    int n = strlen( section );
    return ( buf[0] == '[' && buf[n+1] == ']' && !strncmp( &buf[1], section, n ) );
}

int conf_key( char* buf, const char* key, int* offset, int* reset ) {
    
    int n = strlen( key );
    int t = n;

    if ( !strncmp( buf, key, n ) ) {
        while( isspace(buf[t]) || buf[t] == '=' ) {++t;}
        *offset += t;
        return 1;
    }

    if ( buf[0] == '[' ) {
        *reset = 0;
    }

    return 0;
}

void* conf_read( char* buf, size_t len, const char* section, const char* key ) {

    fseek( conf_fp, 0, SEEK_SET );
    ssize_t read;
    int sec = 0;

    while ( (read = getline( &buf, &len, conf_fp )) > -1 ) {

        int i = -1;
        while( isspace(buf[++i]) );

        if ( buf[i] == '\0' || buf[i] == '#' ) { continue; }

        if ( !sec ) {
            sec = conf_section( &buf[i], section );
        
        } else if ( conf_key( &buf[i], key, &i, &sec ) ) {
            return (void*) &buf[i];
        }
    }
    return NULL;
}

float conf_float( const char* section, const char* key ) {

    size_t len = 25;
    char* buf = (char*) malloc( len * sizeof(char) );

    void* fptr = conf_read( buf, len, section, key );
    float result = 0;

    if ( fptr ) {
        result = atof( fptr );
    }

    free( buf );
    return result;
}

int conf_int( const char* section, const char* key ) {

    size_t len = 25;
    char* buf = (char*) malloc( len * sizeof(char) );

    void* fptr = conf_read( buf, len, section, key );
    int result = 0;

    if ( fptr ) {
        result = atoi( fptr );
    }

    free( buf );
    return result;
}

char* conf_string( const char* section, const char* key ) {

    size_t len = 25;
    char* buf = (char*) malloc( len * sizeof(char) );

    void* sptr = conf_read( buf, len, section, key );
    char* result = NULL;

    if ( sptr ) {
        int n = strlen( sptr );
        result = (char*) malloc( n+1 * sizeof(char) );
        result[n] = '\0';
        strncpy(result, sptr, n);
    }

    free( buf );
    return result;
}

void conf_init( const char* path ) {
    conf_fp = fopen( path, "r" );
}

void conf_close( void ) {
    fclose( conf_fp );
}