#ifndef GRAPHICS_H
#define GRAPHICS_h

#include "env.h"

int graphics_init( const char* gif_path );

void graphics_start_gif( environment* env, const char* fname );

void graphics_add_frame( environment* env );

void graphics_generate_gif( void );

#endif