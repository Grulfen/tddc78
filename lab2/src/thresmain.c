#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ppmio.h"
#include "thresfilter.h"
#include <pthread.h>

int main (int argc, char ** argv) {
        int xsize, ysize, colmax;

        /* Take care of the arguments */
        if (argc != 4) {
                fprintf(stderr, "Usage: %s num_threads infile outfile\n", argv[0]);
                exit(1);
        }

        pixel *src = (pixel*)malloc(sizeof(pixel)*MAX_PIXELS);
        /* read file */
        if(read_ppm (argv[2], &xsize, &ysize, &colmax, (char *) src) != 0){
                free(src);
                exit(1);
        }

        if (colmax > 255) {
                printf("Colmax = %d\n", colmax);
                fprintf(stderr, "Too large maximum color-component value\n");
                free(src);
                exit(1);
        }


        int NUM_THREADS = atoi(argv[1]);
        int i, ret;
        unsigned long g_sum = 0;
        struct timespec stime, etime;

        // Threads
        pthread_t threads[NUM_THREADS];

        // Structs containing the data for the threads
        pixel_n *pdata[NUM_THREADS];
        int pix_p_thread;

        printf("Has read the image, calling filter\n");

        clock_gettime(CLOCK_REALTIME, &stime);

        pix_p_thread = xsize*ysize/NUM_THREADS;

        for(i=0;i<NUM_THREADS;i++){
                pdata[i] = malloc(sizeof(pixel_n));
                pdata[i]->src = src + i*pix_p_thread;
                pdata[i]->n = pix_p_thread;
                if(i == NUM_THREADS - 1){
                        pdata[i]->n += xsize*ysize - pix_p_thread*NUM_THREADS;
                }
                pdata[i]->sum = malloc(sizeof(int));
                *(pdata[i]->sum) = 0;
                ret = pthread_create(&threads[i], NULL, threshold, (void*)pdata[i]);
                if(ret) {
                        fprintf(stderr, "ERROR creating thread\n");
                        free(pdata[i]->sum);
                        free(pdata[i]);
                        free(src);
                        exit(-1);
                }
        }

        for(i=0;i<NUM_THREADS;i++){
                pthread_join(threads[i], NULL);
                g_sum += *(pdata[i]->sum);
                free(pdata[i]->sum);
        }

        for(i=0;i<NUM_THREADS;i++){
                pdata[i]->threshold_value = g_sum/(xsize*ysize);
                pthread_create(&threads[i], NULL, thresfilter, (void*)pdata[i]);
        }

        for(i=0;i<NUM_THREADS;i++){
                pthread_join(threads[i], NULL);
                free(pdata[i]);
        }

        clock_gettime(CLOCK_REALTIME, &etime);

        printf("Filtering took: %g secs\n", (etime.tv_sec  - stime.tv_sec) +
                        1e-9*(etime.tv_nsec  - stime.tv_nsec)) ;

        /* write result */
        printf("Writing output file\n");

        if(write_ppm (argv[3], xsize, ysize, (char *)src) != 0){
                fprintf(stderr, "Error writing file\n");
                free(src);
                exit(1);
        }

        free(src);
        return(0);
}
