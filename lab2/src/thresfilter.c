#include "thresfilter.h"
#include<stdlib.h>
#include<pthread.h>
#include<stdio.h>

#define uint unsigned int 

void *threshold(void *pdata){

        int n = ((pixel_n*)pdata)->n;
        pixel *src = ((pixel_n*)pdata)->src;

        int i;
        int *sum = ((pixel_n*)pdata)->sum;

        for(i = 0; i < n; i++) {
                *sum += (uint)src[i].r + (uint)src[i].g + (uint)src[i].b;
        }
        pthread_exit(NULL);
}

void *thresfilter(void *pdata){

        uint i, psum, nump = ((pixel_n*)pdata)->n;
        pixel *src = ((pixel_n*)pdata)->src;
        uint threshold_value = ((pixel_n*)pdata)->threshold_value;

        for(i = 0; i < nump; i++) {
                psum = (uint)src[i].r + (uint)src[i].g + (uint)src[i].b;
                if(threshold_value > psum) {
                        src[i].r = src[i].g = src[i].b = 0;
                }
                else {
                        src[i].r = src[i].g = src[i].b = 255;
                }
        }
        pthread_exit(NULL);
}
