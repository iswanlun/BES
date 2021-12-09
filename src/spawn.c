#include <stdlib.h>
#include <string.h>

#include "spawn.h"
#include "rand.h"
#include "env.h"
#include "brain.h"

#define MUTATION_FEQ 1000

/* Remap the gene indices from 128 values to set limits  */
#define TRIM(g, i, o) ( ( (((g >> 24) & 0x7F) % i) << 24 ) | \
                        ( (((g >> 16) & 0x7F) % o) << 16 ) | \
                        ( g & 0x8080FFFF ) )

/* Given a set of raw genes, creates and sets up a series
 * interal brain buffers to hold simulation usable versions. */
void spawn_create_pathways( brain* br ) {

    br->cognition_len = 0;
    br->sense_len = 0;

    /* count the number of pathways */
    for( int i = 0; i < br->raw_genome_len; ++i ) {

        if ( IN_SRC( br->raw_genome[i] ) ) {    /* Cognition source */
            br->cognition_len++;
        } else {                                /* Sense source */
            br->sense_len++;
        }
    }

    /* create appropriate buffers */
    br->sense_n     = (uint32_t*) calloc( br->sense_len,     sizeof( uint32_t ) );
    br->cognition_n = (uint32_t*) calloc( br->cognition_len, sizeof( uint32_t ) );

    int sense_index = 0, cog_index = 0;

    /* fill buffers */
    for( int i = 0; i < br->raw_genome_len; ++i ) {

        uint32_t gene = br->raw_genome[i];

        if ( IN_SRC( gene ) ) {         /* Cognition source */

            if ( OUT_SRC( gene) ) {     /* motor out */
                br->cognition_n[cog_index++] = TRIM( gene, COGNITION_COUNT, MOTOR_COUNT );

            } else {                    /* cognition out */
                br->cognition_n[cog_index++] = TRIM( gene, COGNITION_COUNT, COGNITION_COUNT );
            }
            
        } else {                        /* Sense source */

            if ( OUT_SRC( gene) ) {     /* motor out */
                br->cognition_n[sense_index++] = TRIM( gene, SENSE_COUNT, MOTOR_COUNT );

            } else {                    /* cognition out */
                br->cognition_n[sense_index++] = TRIM( gene, SENSE_COUNT, COGNITION_COUNT );
            }
        }
    }
}

brain* spawn_new( int genome_size ) {

    brain* br = (brain*) calloc( 1, sizeof(brain) );
    br->raw_genome = (uint32_t*) calloc( genome_size, sizeof(uint32_t) );

    br->raw_genome_len = genome_size;

    for ( int i = 0; i < genome_size; ++i ) {

        br->raw_genome[i] = rand_next( 0 );
    }

    spawn_create_pathways( br );

    return br;
}

brain* spawn_breed( brain* parent ) {

    brain* br = (brain*) calloc( 1, sizeof(brain) );
    br->raw_genome = (uint32_t*) calloc( parent->raw_genome_len, sizeof(uint32_t) );

    br->raw_genome_len = parent->raw_genome_len;

    memcpy( br->raw_genome, parent->raw_genome, ( parent->raw_genome_len * sizeof( uint32_t ) ) );

    if ( ( rand_next( 0 ) % MUTATION_FEQ ) == 0 ) {

        int steps = rand_next( 0 ) % parent->raw_genome_len;
        int shift = rand_next( 0 ) % 32;

        br->raw_genome[steps] ^= (1 << shift); /* bit flip mutation */
    }
    return br;
}

void spawn_remove( brain* br ) {

    free( br->raw_genome );
    free( br->sense_n );
    free( br->cognition_n );

    br->raw_genome = NULL;
    br->sense_n = NULL;
    br->cognition_n = NULL;

    free( br );
}