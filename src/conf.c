#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "conf.h"

static FILE* conf_fp;

int conf_section( char* buf, size_t len, const char* section ) {

    int n = strlen( section );
    if ( len < n+2 ) { return 0; }

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

void* conf_read( char** buf_ptr, const char* section, const char* key ) {

    fseek( conf_fp, 0, SEEK_SET );
    ssize_t read, len = 0;
    int sec = 0;

    while ( (read = getline( buf_ptr, &len, conf_fp )) > -1 ) {

        char* buf = *buf_ptr;
        int i = -1;

        while( isspace(buf[++i]) );

        if ( buf[i] == '\0' || buf[i] == '#' ) { continue; }

        if ( !sec ) {
            sec = conf_section( &buf[i], read, section );
        
        } else if ( conf_key( &buf[i], key, &i, &sec ) ) {
            return (void*) &buf[i];
        }
    }
    return NULL;
}

float conf_float( const char* section, const char* key ) {

    char* buf = NULL, **buf_ptr = &buf;
    float result = 0;
    void* fptr = conf_read( buf_ptr, section, key );

    if ( fptr ) {
        result = atof( fptr );
    }

    free( *buf_ptr );
    return result;
}

int conf_int( const char* section, const char* key ) {

    char* buf = NULL, **buf_ptr = &buf;
    int result = 0;
    void* fptr = conf_read( buf_ptr, section, key );

    if ( fptr ) {
        result = atoi( fptr );
    }

    free( *buf_ptr );
    return result;
}

char* conf_string( const char* section, const char* key ) {

    char* buf = NULL, **buf_ptr = &buf;
    char* result = NULL;
    void* sptr = conf_read( buf_ptr, section, key );

    if ( sptr ) {
        int n = strlen( sptr );
        result = (char*) malloc( n * sizeof(char) );
        strncpy(result, sptr, n);
        result[n-1] = '\0';
    }

    free( *buf_ptr );
    return result;
}

void conf_init( const char* path ) {
    conf_fp = fopen( path, "r" );
}

void conf_teardown( void ) {
    fclose( conf_fp );
}