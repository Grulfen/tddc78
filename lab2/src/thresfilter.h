/*
  File: thresfilter.h

  Declaration of pixel structure and thresfilter function.
    
 */
#ifndef _THRESFILTER_H_
#define _THRESFILTER_H_
/* NOTE: This structure must not be padded! */
typedef struct _pixel {
    unsigned char r,g,b;
} pixel;

// struct pixel_n
// Contains the pointer to the pixel array,
// pointer to sum to return the sum of pixel values to main program and
// threshold_value
typedef struct _pixel_n {
    pixel* src;
    int n;
    unsigned long *sum;
    unsigned long threshold_value;
} pixel_n;

void *thresfilter(void *pdata);
void *threshold(void *pdata);

#endif
