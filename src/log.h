#ifndef LOG_H
#define LOG_H

#include "env.h"

int log_init( const char* log_path );

void log_itteration( environment* env );

void log_generation( environment* env, int survivors );

void log_sim_issue( const char* err );

void log_msg( const char* msg );

#endif