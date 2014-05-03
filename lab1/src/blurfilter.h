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

void blurfilter_x(const int xsize, const int ysize, pixel* src, const int radius, const double *w);

// shadow_up and shadow_down indicate if there are shadow pixels above or below
// respectively. 0 indicates no shadow elements and 1 indicates shadow elements
void blurfilter_y(const int xsize, const int ysize, pixel* src, const int radius, const double *w, int shadow_up, int shadow_down);

#endif
