#!/bin/bash

for THREADS in {1..20}
do
        echo "" > "../result/blur/times_${THREADS}.txt"
        for image in {1..4}
        do
                for radius in 4 8 16 32
                do
                        echo "Image $image - 9 runs radius $radius" >> "../result/blur/times_${THREADS}.txt"
                        echo "" >> "../result/blur/times_${THREADS}.txt"
                        for i in {1..9}
                        do
                                ./blurc $THREADS $radius "../../images/im${image}.ppm" /dev/null >> "../result/blur/times_${THREADS}.txt"
                        done 
                        echo "" >> "../result/blur/times_${THREADS}.txt"
                done
        done
done
