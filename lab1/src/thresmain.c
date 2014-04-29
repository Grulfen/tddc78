#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <mpi.h>
#include <math.h>
#include "ppmio.h"
#include "thresfilter.h"

void exit_prog(pixel *src, int status)
{
        free(src);
        exit(status);
}

int main (int argc, char ** argv) {

        MPI_Status status;
        MPI_Init(NULL, NULL);

        int myid;
        int n;

        MPI_Comm_rank( MPI_COMM_WORLD, &myid );
        MPI_Comm_size( MPI_COMM_WORLD, &n );

        int xsize, ysize, colmax;
        double start_time, end_time;

        int size;
        int lsize;
        long sum;

        long global_sum;

        pixel *src;

        if(myid == 0){
                /* read file only in one processor */
                src = (pixel*) malloc(sizeof(pixel)*MAX_PIXELS);
                /* Take care of the arguments */
                if (argc != 3) {
                        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
                        exit_prog(src, 1);
                }
                if(read_ppm (argv[1], &xsize, &ysize, &colmax, (char *) src) != 0){
                        exit_prog(src, 1);
                }
                if (colmax > 255) {
                        fprintf(stderr, "Too large maximum color-component value\n");
                        exit_prog(src, 1);
                }
                /* printf("%d: Has read the image, calling filter\n", myid); */
                size = xsize*ysize;
        }

        start_time = MPI_Wtime();

        // Broadcast number of pixels to all processes
	MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);

        lsize = size/n;

        // Local part of image
        pixel *lsrc = (pixel*) malloc(sizeof(pixel)*lsize);
        /* pixel lsrc[lsize]; */

        // Scatter total image to multiple smaller parts for each process
        MPI_Scatter(src, sizeof(pixel)*lsize, MPI_BYTE, lsrc,
                        sizeof(pixel)*lsize, MPI_BYTE, 0, MPI_COMM_WORLD);

        // Sum the pixel values of local part of image
        sum = threshold(lsrc, lsize);

        // Sum all the local sums to a global sum
        MPI_Allreduce(&sum, &global_sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

        // Run the filter with the calculated threshold (global sum/number of pixels)
	thresfilter(lsize, lsrc, global_sum/size);

        // First process runs the filter on the remaining pixels due to size not evenly divisible by n
        if(myid == 0){
                thresfilter(size%n, src + lsize*n, global_sum/size);
        }

        // Gather all the parts of the image to the total image in process 0
        MPI_Gather(lsrc, sizeof(pixel)*lsize, MPI_BYTE, src, sizeof(pixel)*lsize, MPI_BYTE, 0, MPI_COMM_WORLD);

        end_time = MPI_Wtime();

        if(myid == 0){
                printf("Filtering took: %g secs\n", (end_time - start_time));

                /* write result */
                /* printf("Writing output file\n"); */

                if(write_ppm (argv[2], xsize, ysize, (char *)src) != 0){
                        exit_prog(src, 1);
                }
                free(src);
        }

        free(lsrc);

        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Finalize();
        return(0);
}
