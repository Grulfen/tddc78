#include "thresfilter.h"
#include <stdio.h>

void thresfilter(const unsigned int nump, pixel* src, unsigned int threshold_value)
{
#define uint unsigned int 

        uint i, psum;

        for(i = 0; i < nump; i++) {
                psum = (uint)src[i].r + (uint)src[i].g + (uint)src[i].b;
                if(threshold_value > psum) {
                        src[i].r = src[i].g = src[i].b = 0;
                }
                else {
                        src[i].r = src[i].g = src[i].b = 255;
                }
        }
}

int threshold(pixel* src, int n)
{
        int i, sum;
        for(i = 0, sum = 0; i < n; i++) {
                sum += (uint)src[i].r + (uint)src[i].g + (uint)src[i].b;
        }
        return sum;
}
