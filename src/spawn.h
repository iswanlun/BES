#ifndef SPAWN_H
#define SPAWN_H

#include "brain.h"

/* Create a new brain with a fixed genome size */
brain* spawn_new( int genome_size );

/* Create a new child from a successful parent with variation.
 * Genes are created from the parents genome, on creation brain
 * genome pathway vectors are populated with model correct values.
 */
brain* spawn_breed( brain* parent );

/* cleans up brain resources */
void spawn_remove( brain* eol );

#endif