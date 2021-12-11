#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include "graphics.h"
#include "gd.h"

#define IMG_SCALE 4

static FILE* gif_fp;
static const char* path;
static gdImage* im_p;

static int tsp;
static int img_x_dim;
static int img_y_dim;

int graphics_init( const char* gif_path ) {

    path = gif_path;
    struct stat st;

    return ( stat(path, &st) | !S_ISDIR(st.st_mode) );
}

/* start a new gif animation */
void graphics_start_gif( environment* env, const char* fname ) {

    char fpath[ strlen(path) + strlen(fname) ];
    sprintf( fpath, "%s%s_Gen_%d.gif", path, fname, env->gen );
    gif_fp = fopen( fpath, "wb" );

    img_x_dim = (env->x_dim * IMG_SCALE);
    img_y_dim = (env->y_dim * IMG_SCALE);

    im_p = gdImageCreate(img_x_dim, img_y_dim);
    gdImageColorAllocate(im_p, 255, 255, 255); /* white background */
    tsp = gdImageColorAllocate(im_p, 1, 1, 1); /* allows transparent pixels */
    
    for ( int i = 0; i < env->population; ++i ) {

        uint32_t fgene = env->brains[i]->raw_genome[0];
        env->brains[i]->color = gdImageColorAllocate( im_p, ((fgene>>24) & 0xFF), ((fgene>>16) & 0xFF), ((fgene>>8) & 0xFF) );
    }

    gdImageGifAnimBegin( im_p, gif_fp, 1, 0 );
}

/* Create and add new frame to gif */
void graphics_add_frame( environment* env ) {

    gdImage* im_c = gdImageCreate(img_x_dim, img_y_dim);
    gdImageColorAllocate( im_c, 255, 255, 255 );
    gdImagePaletteCopy(im_c, im_p);  /* Make sure the palette is identical */
    gdImageColorTransparent( im_c, tsp );

    for ( int i = 0; i < env->population; ++i ) {

        int x = (env->brains[i]->x_pos * IMG_SCALE);
        int y = (env->brains[i]->y_pos * IMG_SCALE);

        gdImageFilledRectangle(im_c, x, y, x+(IMG_SCALE-1), y+(IMG_SCALE-1), env->brains[i]->color );
    }

    gdImageGifAnimAdd(im_c, gif_fp, 0, 0, 0, 30, 3, NULL );
    gdImageDestroy(im_p);
    im_p = im_c;
}

/* generate gif, dispose of all resources */
void graphics_generate_gif( void ) {

    gdImageGifAnimEnd( gif_fp );
    gdImageDestroy( im_p );
    fclose( gif_fp );    
}