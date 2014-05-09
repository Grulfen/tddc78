/*
  File: blurfilter.c

  Implementation of blurfilter function.
    
 */
#include <stdio.h>
#include "blurfilter.h"
#include "ppmio.h"

int min(int a, int b)
{
	return a<b ? a : b;
}


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

// blurfilter_x
// filter the image along the x-axis.
// The result is saved in the dst pointer
void* blurfilter_x(void* p)
{
	blur_data* blur_p = (blur_data*)p;

	const int xsize = blur_p->xsize;
	const int ysize = blur_p->ysize;
	pixel *src = blur_p->src;
	pixel *dst = blur_p->dst;
	const int radius = blur_p->radius;
	const double *w = blur_p->w;

	int x,y,x2, wi;
	double r,g,b,n, wc;

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
        return NULL;
}

// Filter along y-axis
// The result is saved in src pointer (SIC)
void* blurfilter_y(void* p){
	blur_data* blur_p = (blur_data*)p;

	const int xsize = blur_p->xsize;
	const int ysize = blur_p->ysize;

	// Use dst from x-filter as source for y-filter
	pixel *src = blur_p->dst;
	pixel *dst = blur_p->src;
	const int radius = blur_p->radius;
	const double *w = blur_p->w;
	int rows_up = blur_p->rows_up;
	int rows_down = blur_p->rows_down;

        int x,y,y2, wi;
        double r,g,b,n, wc;

        for (y=0; y<ysize; y++) {
                for (x=0; x<xsize; x++) {
                        r = w[0] * pix(src, x, y, xsize)->r;
                        g = w[0] * pix(src, x, y, xsize)->g;
                        b = w[0] * pix(src, x, y, xsize)->b;
                        n = w[0];
                        for ( wi=1; wi <= radius; wi++) {
                                wc = w[wi];
                                y2 = y - wi;
				// Use pixels above for filtering
				// but do not go outside original image
                                if(y2 >= -min(radius, rows_up)) {
                                        r += wc * pix(src, x, y2, xsize)->r;
                                        g += wc * pix(src, x, y2, xsize)->g;
                                        b += wc * pix(src, x, y2, xsize)->b;
                                        n += wc;
                                }
                                y2 = y + wi;
				// Use pixels below for filtering
				// but do not go outside original image
                                if(y2 < ysize + min(radius, rows_down)) {
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
        return NULL;
}
