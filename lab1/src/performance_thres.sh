#!/bin/bash
#
#SBATCH -J perfomance_test
#SBATCH -t 20
#SBATCH -o results/batch_thress.txt
#

echo "Image 1 - 9 runs"
echo ""
mpprun ./thresc images/im1.ppm results/threshold/batch_thress1.ppm
mpprun ./thresc images/im1.ppm results/threshold/batch_thress1.ppm
mpprun ./thresc images/im1.ppm results/threshold/batch_thress1.ppm
mpprun ./thresc images/im1.ppm results/threshold/batch_thress1.ppm
mpprun ./thresc images/im1.ppm results/threshold/batch_thress1.ppm
mpprun ./thresc images/im1.ppm results/threshold/batch_thress1.ppm
mpprun ./thresc images/im1.ppm results/threshold/batch_thress1.ppm
mpprun ./thresc images/im1.ppm results/threshold/batch_thress1.ppm
mpprun ./thresc images/im1.ppm results/threshold/batch_thress1.ppm

echo ""
echo "Image 2 - 9 runs"
echo ""

mpprun ./thresc images/im2.ppm results/threshold/batch_thress2.ppm
mpprun ./thresc images/im2.ppm results/threshold/batch_thress2.ppm
mpprun ./thresc images/im2.ppm results/threshold/batch_thress2.ppm
mpprun ./thresc images/im2.ppm results/threshold/batch_thress2.ppm
mpprun ./thresc images/im2.ppm results/threshold/batch_thress2.ppm
mpprun ./thresc images/im2.ppm results/threshold/batch_thress2.ppm
mpprun ./thresc images/im2.ppm results/threshold/batch_thress2.ppm
mpprun ./thresc images/im2.ppm results/threshold/batch_thress2.ppm
mpprun ./thresc images/im2.ppm results/threshold/batch_thress2.ppm

echo ""
echo "Image 3 - 9 runs"
echo ""

mpprun ./thresc images/im3.ppm results/threshold/batch_thress3.ppm
mpprun ./thresc images/im3.ppm results/threshold/batch_thress3.ppm
mpprun ./thresc images/im3.ppm results/threshold/batch_thress3.ppm
mpprun ./thresc images/im3.ppm results/threshold/batch_thress3.ppm
mpprun ./thresc images/im3.ppm results/threshold/batch_thress3.ppm
mpprun ./thresc images/im3.ppm results/threshold/batch_thress3.ppm
mpprun ./thresc images/im3.ppm results/threshold/batch_thress3.ppm
mpprun ./thresc images/im3.ppm results/threshold/batch_thress3.ppm
mpprun ./thresc images/im3.ppm results/threshold/batch_thress3.ppm

echo ""
echo "Image 4 - 9 runs"
echo ""

mpprun ./thresc images/im4.ppm results/threshold/batch_thress4.ppm
mpprun ./thresc images/im4.ppm results/threshold/batch_thress4.ppm
mpprun ./thresc images/im4.ppm results/threshold/batch_thress4.ppm
mpprun ./thresc images/im4.ppm results/threshold/batch_thress4.ppm
mpprun ./thresc images/im4.ppm results/threshold/batch_thress4.ppm
mpprun ./thresc images/im4.ppm results/threshold/batch_thress4.ppm
mpprun ./thresc images/im4.ppm results/threshold/batch_thress4.ppm
mpprun ./thresc images/im4.ppm results/threshold/batch_thress4.ppm
mpprun ./thresc images/im4.ppm results/threshold/batch_thress4.ppm

#
