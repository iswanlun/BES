#ifndef CONF_H
#define CONF_H

void conf_init( const char* path );

void conf_teardown( void );

char* conf_string( const char* section, const char* key );

float conf_float( const char* section, const char* key );

int conf_int( const char* section, const char* key );

#endif