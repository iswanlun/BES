#ifndef SPAWN_H
#define SPAWN_H

#include "brain.h"

brain* spawn_new( int genome_size );

/* Create a new child from a successful parent with variation.
 * Variations are assured to be valid. ( % on creation ) */
brain* spawn_breed( brain* parent );

/* cleans up brain resources */
void spawn_remove( brain* eol );

#endif