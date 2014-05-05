#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include "ppmio.h"
#include "blurfilter.h"
#include "gaussw.h"

#define MAX_RAD 1000

void exit_prog(pixel *src, pixel *dst, int status)
{
	free(src);
	free(dst);
	exit(status);
}

int main (int argc, char ** argv) {
	int radius, ret;
	int xsize, ysize, colmax, i;
	struct timespec stime, etime;

	double w[MAX_RAD];

	pixel *src = (pixel*) malloc(sizeof(pixel)*MAX_PIXELS);
	pixel *dst = (pixel*) malloc(sizeof(pixel)*MAX_PIXELS);
	/* Take care of the arguments */
	if (argc != 5) {
		fprintf(stderr, "Usage: %s num_threads radius infile outfile\n", argv[0]);
		exit_prog(src, dst, 1);
	}

	int num_threads = atoi(argv[1]);
	radius = atoi(argv[2]);
	if((radius > MAX_RAD) || (radius < 1)) {
		fprintf(stderr, "Radius (%d) must be greater than zero and less then %d\n",
				radius, MAX_RAD);
		exit_prog(src, dst, 1);
	}

	/* read file */
	if(read_ppm (argv[3], &xsize, &ysize, &colmax, (char *) src) != 0){
		exit_prog(src, dst, 1);
	}

	if( num_threads < 1 || num_threads > ysize){
		fprintf(stderr, "Number of threads needs to be bigger than 0 and smaller than ysize of image\n");
		exit_prog(src, dst, 1);
	}

	if (colmax > 255) {
		fprintf(stderr, "Too large maximum color-component value\n");
		exit_prog(src, dst, 1);
	}

	pthread_t threads[num_threads];
	blur_data *pdata[num_threads];

	int l_ysize = ysize/num_threads;

	// Calculate gauss weights
	get_gauss_weights(radius, w);

	printf("Calling filter\n");

	clock_gettime(CLOCK_REALTIME, &stime);

	for(i=0;i<num_threads;i++){
		pdata[i] = malloc(sizeof(blur_data));
		pdata[i]->xsize = xsize;
		pdata[i]->ysize = l_ysize;
		if(i == num_threads - 1){
			pdata[i]->ysize += ysize - l_ysize*num_threads;
		}
		pdata[i]->src = src + i*l_ysize*xsize;
		pdata[i]->dst = dst + i*l_ysize*xsize;
		pdata[i]->radius = radius;
		pdata[i]->w = w;
		// Number of rows above the threads part of the image
		pdata[i]->rows_up = i*l_ysize;
		// Number of rows below the threads part of the image
		pdata[i]->rows_down = ysize - l_ysize - pdata[i]->rows_up;
		ret = pthread_create(&threads[i], NULL, blurfilter_x, (void*)pdata[i]);
		if(ret){
			fprintf(stderr, "ERROR creating thread\n");
                        free(pdata[i]);
			exit_prog(src, dst, 1);
		}
	}

        for(i=0;i<num_threads;i++){
                pthread_join(threads[i], NULL);
        }

        for(i=0;i<num_threads;i++){
		ret = pthread_create(&threads[i], NULL, blurfilter_y, (void*)pdata[i]);
		if(ret){
			fprintf(stderr, "ERROR creating thread\n");
                        free(pdata[i]);
			exit_prog(src, dst, 1);
		}
        }

        for(i=0;i<num_threads;i++){
                pthread_join(threads[i], NULL);
        }

	clock_gettime(CLOCK_REALTIME, &etime);

	printf("Filtering took: %g secs\n", (etime.tv_sec  - stime.tv_sec) +
			1e-9*(etime.tv_nsec  - stime.tv_nsec)) ;

	/* write result */
	printf("Writing output file\n");

	if(write_ppm (argv[4], xsize, ysize, (char *)src) != 0){
		exit_prog(src, dst, 1);
	}

	free(src);
	free(dst);

	return 0;
}
