#!/bin/bash

for THREADS in {1..20}
do
        echo "" > "../result/threshold/times_${THREADS}.txt"
        for image in {1..4}
        do
                echo "Image $image - 9" >> "../result/threshold/times_${THREADS}.txt"
                echo "" >> "../result/threshold/times_${THREADS}.txt"
                for i in {1..9}
                do
                        ./thresc $THREADS "../../images/im${image}.ppm" /dev/null >> "../result/threshold/times_${THREADS}.txt"
                done 
                echo "" >> "../result/threshold/times_${THREADS}.txt"
        done
done
