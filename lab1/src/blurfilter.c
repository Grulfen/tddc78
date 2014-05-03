/*
File: blurfilter.c

Implementation of blurfilter function.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blurfilter.h"
#include "ppmio.h"


pixel* pix(pixel* image, const int xx, const int yy, const int xsize)
{
        register int off = xsize*yy + xx;

#ifdef DBG
        if(off >= MAX_PIXELS) {
                fprintf(stderr, "\n Terribly wrong: %d %d %d\n",xx,yy,xsize);
        }
#endif
        return (image + off);
}

void blurfilter_x(const int xsize, const int ysize, pixel* src, const int radius, const double *w){
        int x,y,x2, wi;
        double r,g,b,n, wc;

        // Use malloc to avoid stack overflow
        pixel *dst = (pixel*) malloc(sizeof(pixel)*MAX_PIXELS);


        for (y=0; y<ysize; y++) {
                for (x=0; x<xsize; x++) {
                        r = w[0] * pix(src, x, y, xsize)->r;
                        g = w[0] * pix(src, x, y, xsize)->g;
                        b = w[0] * pix(src, x, y, xsize)->b;
                        n = w[0];
                        for ( wi=1; wi <= radius; wi++) {
                                wc = w[wi];
                                x2 = x - wi;
                                if(x2 >= 0) {
                                        r += wc * pix(src, x2, y, xsize)->r;
                                        g += wc * pix(src, x2, y, xsize)->g;
                                        b += wc * pix(src, x2, y, xsize)->b;
                                        n += wc;
                                }
                                x2 = x + wi;
                                if(x2 < xsize) {
                                        r += wc * pix(src, x2, y, xsize)->r;
                                        g += wc * pix(src, x2, y, xsize)->g;
                                        b += wc * pix(src, x2, y, xsize)->b;
                                        n += wc;
                                }
                        }
                        pix(dst,x,y, xsize)->r = r/n;
                        pix(dst,x,y, xsize)->g = g/n;
                        pix(dst,x,y, xsize)->b = b/n;
                }
        }

        // Copy filtered data to src pointer
        memcpy(src,dst, xsize*ysize*sizeof(pixel));
        free(dst);
}

// shadow_up and shadow_down indicate if there are shadow pixels above or below
// respectively. 0 indicates no shadow elements and 1 indicates shadow elements
void blurfilter_y(const int xsize, const int ysize, pixel* src, const int radius, const double *w, int shadow_up, int shadow_down){
        int x,y,y2, wi;
        double r,g,b,n, wc;
        // Use malloc to avoid stack overflow
        pixel *dst = (pixel*) malloc(sizeof(pixel)*MAX_PIXELS);
        for (y=0; y<ysize; y++) {
                for (x=0; x<xsize; x++) {
                        r = w[0] * pix(src, x, y, xsize)->r;
                        g = w[0] * pix(src, x, y, xsize)->g;
                        b = w[0] * pix(src, x, y, xsize)->b;
                        n = w[0];
                        for ( wi=1; wi <= radius; wi++) {
                                wc = w[wi];
                                y2 = y - wi;
                                // If there is shadow elements above, use them
                                // in filtering. (Can be elements before
                                // src pointer
                                if(y2 >= -radius*shadow_up) {
                                        r += wc * pix(src, x, y2, xsize)->r;
                                        g += wc * pix(src, x, y2, xsize)->g;
                                        b += wc * pix(src, x, y2, xsize)->b;
                                        n += wc;
                                }
                                y2 = y + wi;
                                // If there is shadow elements below, use them
                                // in filtering. (Can be elements after 
                                // src pointer + xsize*ysize
                                if(y2 < ysize + radius*shadow_down) {
                                        r += wc * pix(src, x, y2, xsize)->r;
                                        g += wc * pix(src, x, y2, xsize)->g;
                                        b += wc * pix(src, x, y2, xsize)->b;
                                        n += wc;
                                }
                        }
                        pix(dst,x,y, xsize)->r = r/n;
                        pix(dst,x,y, xsize)->g = g/n;
                        pix(dst,x,y, xsize)->b = b/n;
                }
        }

        // Copy filtered data to src pointer
        memcpy(src, dst, xsize*ysize*sizeof(pixel));
        free(dst);
}
