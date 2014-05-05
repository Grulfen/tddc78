/*
  File: blurfilter.h

  Declaration of pixel structure and blurfilter function.
    
 */

#ifndef _BLURFILTER_H_
#define _BLURFILTER_H_

/* NOTE: This structure must not be padded! */
typedef struct _pixel {
    unsigned char r,g,b;
} pixel;

typedef struct _blur_data {
    int xsize;
    int ysize;
    pixel *src;
    pixel *dst;
    int radius;
    const double *w;
    int rows_up;
    int rows_down;
} blur_data;

void* blurfilter_x(void* p);

void* blurfilter_y(void* p);

#endif
