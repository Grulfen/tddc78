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

typedef struct _pixel_n {
    pixel* src;
    int n;
    int *sum;
    unsigned int threshold_value;
} pixel_n;

void *thresfilter(void *pdata);
void *threshold(void *pdata);

#endif
