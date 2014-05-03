#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <mpi.h>
#include "ppmio.h"
#include "blurfilter.h"
#include "gaussw.h"


#define MAX_RAD 1000
void exit_prog(pixel *src, int status)
{
        free(src);
        exit(status);
}

int main (int argc, char ** argv)
{

        MPI_Status status;
        MPI_Init(NULL, NULL);

        int myid;
        int n;
        int i;

        MPI_Comm_rank( MPI_COMM_WORLD, &myid );
        MPI_Comm_size( MPI_COMM_WORLD, &n );


        int radius;
        int xsize, ysize, colmax;
        int gauss_root;

        int l_ysize;
        int remain_ysize;
        pixel *src;
        double start_time, end_time;


        double w[MAX_RAD];

        if(myid == 0){
                src = (pixel*) malloc(sizeof(pixel)*MAX_PIXELS);
                /* Take care of the arguments */
                if (argc != 4) {
                        fprintf(stderr, "Usage: %s radius infile outfile\n", argv[0]);
                        exit_prog(src, 1);
                }
                radius = atoi(argv[1]);
                if((radius > MAX_RAD) || (radius < 1)) {
                        fprintf(stderr, "Radius (%d) must be greater than zero and less then %d\n",
                                        radius, MAX_RAD);
                        exit_prog(src, 1);
                }

                /* read file */
                if(read_ppm (argv[2], &xsize, &ysize, &colmax, (char *) src) != 0){
                        exit_prog(src, 1);
                }

                if(radius > ysize/n){
                        fprintf(stderr, "Radius, %d, too big for %d number of processes. Radius must be less than ysize (%d) / number of processes (%d).\n", radius, n, ysize, n);
                }

                if (colmax > 255) {
                        fprintf(stderr, "Too large maximum color-component value\n");
                        exit_prog(src, 1);
                }
                
                // Calculate gauss weights
                get_gauss_weights(radius, w);

        } 

        start_time = MPI_Wtime();

        // MPI broadcasts
        MPI_Bcast(w, MAX_RAD, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast(&radius, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&xsize, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&ysize, 1, MPI_INT, 0, MPI_COMM_WORLD);

        // Calculate local number of rows
        l_ysize = ysize/n;
        remain_ysize = ysize % n;
        pixel *lsrc;
        if( myid == n-1){
                // Handle remaining rows due to integer division
                lsrc = (pixel*) malloc(sizeof(pixel)*(2*radius*xsize + (remain_ysize + l_ysize)*xsize));
        } else {
                lsrc = (pixel*) malloc(sizeof(pixel)*(2*radius*xsize + l_ysize*xsize));
        }

        MPI_Scatter(src, sizeof(pixel)*l_ysize*xsize, MPI_BYTE,
                        lsrc+radius*xsize, sizeof(pixel)*l_ysize*xsize,
                        MPI_BYTE, 0, MPI_COMM_WORLD);

        if(n == 1){
                // If one process no communication
                // Blur the pixels with respect to pixels on x-axis
                blurfilter_x(xsize, ysize, lsrc + radius*xsize, radius, w);
                blurfilter_y(xsize, ysize, lsrc + radius*xsize, radius, w, 0, 0);
        } else {
                if(myid == 0){

                        // Send remaining row to last process
                        MPI_Send(src+n*l_ysize*xsize,
                                        sizeof(pixel)*remain_ysize*xsize,
                                        MPI_BYTE, n-1, 30, MPI_COMM_WORLD);

                        // Blur the pixels with respect to pixels on x-axis
                        blurfilter_x(xsize, l_ysize, lsrc+radius*xsize, radius, w);

                        // First process only receives shadow pixels from pixels of process "below"
                        MPI_Recv(lsrc+(radius+l_ysize)*xsize, sizeof(pixel)*xsize*radius,
                                        MPI_BYTE, myid+1, 10, MPI_COMM_WORLD, &status);
                        // First process only send pixels to shadow pixels of process "below"
                        MPI_Send(lsrc+l_ysize*xsize, sizeof(pixel)*xsize*radius,
                                        MPI_BYTE, myid+1, 20, MPI_COMM_WORLD);

                        // Blur the pixels with respect to pixels on y-axis
                        blurfilter_y(xsize, l_ysize, lsrc+radius*xsize, radius, w, 0, 1);

                        // Receive filtered remaining rows from last process
                        MPI_Recv(src+n*l_ysize*xsize,
                                        sizeof(pixel)*remain_ysize*xsize,
                                        MPI_BYTE, n-1, 30, MPI_COMM_WORLD, &status);

                } else if(myid == n-1){
                        // Receive remaining rows from first process
                        MPI_Recv(lsrc+(radius+l_ysize)*xsize,
                                        sizeof(pixel)*remain_ysize*xsize,
                                        MPI_BYTE, 0, 30, MPI_COMM_WORLD,
                                        &status);

                        // Blur the pixels with respect to pixels on x-axis
                        blurfilter_x(xsize, l_ysize + remain_ysize, lsrc+radius*xsize, radius, w);

                        // Last process only sends pixels to shadow pixels of process "above"
                        MPI_Send(lsrc+radius*xsize, sizeof(pixel)*xsize*radius,
                                        MPI_BYTE, myid-1, 10, MPI_COMM_WORLD);
                        // Last process only receives shadow pixels from pixels of process "above"
                        MPI_Recv(lsrc, sizeof(pixel)*xsize*radius,
                                        MPI_BYTE, myid-1, 20, MPI_COMM_WORLD, &status);

                        // Blur the pixels with respect to pixels on y-axis

                        blurfilter_y(xsize, l_ysize + remain_ysize, lsrc+radius*xsize, radius, w, 1, 0);

                        // Send filtered remaining row to first process
                        MPI_Send(lsrc+(radius + l_ysize)*xsize,
                                        sizeof(pixel)*remain_ysize*xsize,
                                        MPI_BYTE, 0, 30, MPI_COMM_WORLD);

                } else {

                        // Blur the pixels with respect to pixels on x-axis
                        blurfilter_x(xsize, l_ysize, lsrc+radius*xsize, radius, w);
                        
                        // Send pixels to shadow pixels of process "above"
                        MPI_Send(lsrc+radius*xsize, sizeof(pixel)*xsize*radius,
                                        MPI_BYTE, myid-1, 10, MPI_COMM_WORLD);
                        // Recieve shadow pixels from pixels of process "below"
                        MPI_Recv(lsrc+(radius+l_ysize)*xsize, sizeof(pixel)*xsize*radius,
                                        MPI_BYTE, myid+1, 10, MPI_COMM_WORLD, &status);

                        // Send pixels to shadow pixels of process "below"
                        MPI_Send(lsrc+l_ysize*xsize, sizeof(pixel)*xsize*radius,
                                        MPI_BYTE, myid+1, 20, MPI_COMM_WORLD);
                        // Recieve shadow pixels from pixels of process "above"
                        MPI_Recv(lsrc, sizeof(pixel)*xsize*radius,
                                        MPI_BYTE, myid-1, 20, MPI_COMM_WORLD, &status);
                        // Blur the pixels with respect to pixels on y-axis
                        blurfilter_y(xsize, l_ysize, lsrc+radius*xsize, radius, w, 1, 1);
                }
        }


        MPI_Gather(lsrc+radius*xsize, sizeof(pixel)*l_ysize*xsize, MPI_BYTE, src,
                        sizeof(pixel)*l_ysize*xsize, MPI_BYTE, 0, MPI_COMM_WORLD);

        end_time = MPI_Wtime();

        if(myid == 0){
                printf("Filtering took: %g secs\n", (end_time - start_time));

                if(write_ppm (argv[3], xsize, ysize, (char *)src) != 0){
                        exit_prog(src, 1);
                }
                free(src);
        }
        free(lsrc);
        MPI_Finalize();
        return(0);
}
