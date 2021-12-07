#include <stdlib.h>
#include "spawn.h"
#include "rand.h"
#include "neurons.h"

/* Remap the gene indices from 128 values to set limits  */
#define TRIM(g, i, o) ( ( (((g >> 24) & 0x7F) % i) << 24 ) | \
                        ( (((g >> 16) & 0x7F) % o) << 16 ) | \
                        ( g & 0x8080FFFF ) )

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

        br->raw_genome[i] = rand_next( 1 );
    }

    spawn_create_pathways( br );

    return br;
}

brain* spawn_breed( brain* parent ) {

    
}

void spawn_remove( brain* eol ) {


}