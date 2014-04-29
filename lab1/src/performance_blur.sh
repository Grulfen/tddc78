#!/bin/bash
#
#SBATCH -J perfomance_test
#SBATCH -t 20
#SBATCH -o results/blur.txt
#SBATCH -Q
#

echo "Image 1 - 9 runs radius 4"
echo ""
mpprun ./blurc 4 images/im1.ppm results/averaging/batch1_4.ppm
mpprun ./blurc 4 images/im1.ppm results/averaging/batch1_4.ppm
mpprun ./blurc 4 images/im1.ppm results/averaging/batch1_4.ppm
mpprun ./blurc 4 images/im1.ppm results/averaging/batch1_4.ppm
mpprun ./blurc 4 images/im1.ppm results/averaging/batch1_4.ppm
mpprun ./blurc 4 images/im1.ppm results/averaging/batch1_4.ppm
mpprun ./blurc 4 images/im1.ppm results/averaging/batch1_4.ppm
mpprun ./blurc 4 images/im1.ppm results/averaging/batch1_4.ppm
mpprun ./blurc 4 images/im1.ppm results/averaging/batch1_4.ppm


echo ""
echo "Image 1 - 9 runs radius 8"
echo ""

mpprun ./blurc 8 images/im1.ppm results/averaging/batch1_8.ppm
mpprun ./blurc 8 images/im1.ppm results/averaging/batch1_8.ppm
mpprun ./blurc 8 images/im1.ppm results/averaging/batch1_8.ppm
mpprun ./blurc 8 images/im1.ppm results/averaging/batch1_8.ppm
mpprun ./blurc 8 images/im1.ppm results/averaging/batch1_8.ppm
mpprun ./blurc 8 images/im1.ppm results/averaging/batch1_8.ppm
mpprun ./blurc 8 images/im1.ppm results/averaging/batch1_8.ppm
mpprun ./blurc 8 images/im1.ppm results/averaging/batch1_8.ppm
mpprun ./blurc 8 images/im1.ppm results/averaging/batch1_8.ppm

echo ""
echo "Image 1 - 9 runs radius 16"
echo ""

mpprun ./blurc 16 images/im1.ppm results/averaging/batch1_16.ppm
mpprun ./blurc 16 images/im1.ppm results/averaging/batch1_16.ppm
mpprun ./blurc 16 images/im1.ppm results/averaging/batch1_16.ppm
mpprun ./blurc 16 images/im1.ppm results/averaging/batch1_16.ppm
mpprun ./blurc 16 images/im1.ppm results/averaging/batch1_16.ppm
mpprun ./blurc 16 images/im1.ppm results/averaging/batch1_16.ppm
mpprun ./blurc 16 images/im1.ppm results/averaging/batch1_16.ppm
mpprun ./blurc 16 images/im1.ppm results/averaging/batch1_16.ppm
mpprun ./blurc 16 images/im1.ppm results/averaging/batch1_16.ppm

echo ""
echo "Image 1 - 9 runs radius 32"
echo ""

mpprun ./blurc 32 images/im1.ppm results/averaging/batch1_32.ppm
mpprun ./blurc 32 images/im1.ppm results/averaging/batch1_32.ppm
mpprun ./blurc 32 images/im1.ppm results/averaging/batch1_32.ppm
mpprun ./blurc 32 images/im1.ppm results/averaging/batch1_32.ppm
mpprun ./blurc 32 images/im1.ppm results/averaging/batch1_32.ppm
mpprun ./blurc 32 images/im1.ppm results/averaging/batch1_32.ppm
mpprun ./blurc 32 images/im1.ppm results/averaging/batch1_32.ppm
mpprun ./blurc 32 images/im1.ppm results/averaging/batch1_32.ppm
mpprun ./blurc 32 images/im1.ppm results/averaging/batch1_32.ppm

echo ""
echo "Image 2 - 9 runs radius 4"
echo ""

mpprun ./blurc 4 images/im2.ppm results/averaging/batch2_4.ppm
mpprun ./blurc 4 images/im2.ppm results/averaging/batch2_4.ppm
mpprun ./blurc 4 images/im2.ppm results/averaging/batch2_4.ppm
mpprun ./blurc 4 images/im2.ppm results/averaging/batch2_4.ppm
mpprun ./blurc 4 images/im2.ppm results/averaging/batch2_4.ppm
mpprun ./blurc 4 images/im2.ppm results/averaging/batch2_4.ppm
mpprun ./blurc 4 images/im2.ppm results/averaging/batch2_4.ppm
mpprun ./blurc 4 images/im2.ppm results/averaging/batch2_4.ppm
mpprun ./blurc 4 images/im2.ppm results/averaging/batch2_4.ppm

echo ""
echo "Image 2 - 9 runs radius 8"
echo ""

mpprun ./blurc 8 images/im2.ppm results/averaging/batch2_8.ppm
mpprun ./blurc 8 images/im2.ppm results/averaging/batch2_8.ppm
mpprun ./blurc 8 images/im2.ppm results/averaging/batch2_8.ppm
mpprun ./blurc 8 images/im2.ppm results/averaging/batch2_8.ppm
mpprun ./blurc 8 images/im2.ppm results/averaging/batch2_8.ppm
mpprun ./blurc 8 images/im2.ppm results/averaging/batch2_8.ppm
mpprun ./blurc 8 images/im2.ppm results/averaging/batch2_8.ppm
mpprun ./blurc 8 images/im2.ppm results/averaging/batch2_8.ppm
mpprun ./blurc 8 images/im2.ppm results/averaging/batch2_8.ppm

echo ""
echo "Image 2 - 9 runs radius 16"
echo ""

mpprun ./blurc 16 images/im2.ppm results/averaging/batch2_16.ppm
mpprun ./blurc 16 images/im2.ppm results/averaging/batch2_16.ppm
mpprun ./blurc 16 images/im2.ppm results/averaging/batch2_16.ppm
mpprun ./blurc 16 images/im2.ppm results/averaging/batch2_16.ppm
mpprun ./blurc 16 images/im2.ppm results/averaging/batch2_16.ppm
mpprun ./blurc 16 images/im2.ppm results/averaging/batch2_16.ppm
mpprun ./blurc 16 images/im2.ppm results/averaging/batch2_16.ppm
mpprun ./blurc 16 images/im2.ppm results/averaging/batch2_16.ppm
mpprun ./blurc 16 images/im2.ppm results/averaging/batch2_16.ppm

echo ""
echo "Image 2 - 9 runs radius 32"
echo ""

mpprun ./blurc 32 images/im2.ppm results/averaging/batch2_32.ppm
mpprun ./blurc 32 images/im2.ppm results/averaging/batch2_32.ppm
mpprun ./blurc 32 images/im2.ppm results/averaging/batch2_32.ppm
mpprun ./blurc 32 images/im2.ppm results/averaging/batch2_32.ppm
mpprun ./blurc 32 images/im2.ppm results/averaging/batch2_32.ppm
mpprun ./blurc 32 images/im2.ppm results/averaging/batch2_32.ppm
mpprun ./blurc 32 images/im2.ppm results/averaging/batch2_32.ppm
mpprun ./blurc 32 images/im2.ppm results/averaging/batch2_32.ppm
mpprun ./blurc 32 images/im2.ppm results/averaging/batch2_32.ppm

echo ""
echo "Image 3 - 9 runs radius 4"
echo ""

mpprun ./blurc 4 images/im3.ppm results/averaging/batch3_4.ppm
mpprun ./blurc 4 images/im3.ppm results/averaging/batch3_4.ppm
mpprun ./blurc 4 images/im3.ppm results/averaging/batch3_4.ppm
mpprun ./blurc 4 images/im3.ppm results/averaging/batch3_4.ppm
mpprun ./blurc 4 images/im3.ppm results/averaging/batch3_4.ppm
mpprun ./blurc 4 images/im3.ppm results/averaging/batch3_4.ppm
mpprun ./blurc 4 images/im3.ppm results/averaging/batch3_4.ppm
mpprun ./blurc 4 images/im3.ppm results/averaging/batch3_4.ppm
mpprun ./blurc 4 images/im3.ppm results/averaging/batch3_4.ppm

echo ""
echo "Image 3 - 9 runs radius 8"
echo ""

mpprun ./blurc 8 images/im3.ppm results/averaging/batch3_8.ppm
mpprun ./blurc 8 images/im3.ppm results/averaging/batch3_8.ppm
mpprun ./blurc 8 images/im3.ppm results/averaging/batch3_8.ppm
mpprun ./blurc 8 images/im3.ppm results/averaging/batch3_8.ppm
mpprun ./blurc 8 images/im3.ppm results/averaging/batch3_8.ppm
mpprun ./blurc 8 images/im3.ppm results/averaging/batch3_8.ppm
mpprun ./blurc 8 images/im3.ppm results/averaging/batch3_8.ppm
mpprun ./blurc 8 images/im3.ppm results/averaging/batch3_8.ppm
mpprun ./blurc 8 images/im3.ppm results/averaging/batch3_8.ppm

echo ""
echo "Image 3 - 9 runs radius 16"
echo ""

mpprun ./blurc 16 images/im3.ppm results/averaging/batch3_16.ppm
mpprun ./blurc 16 images/im3.ppm results/averaging/batch3_16.ppm
mpprun ./blurc 16 images/im3.ppm results/averaging/batch3_16.ppm
mpprun ./blurc 16 images/im3.ppm results/averaging/batch3_16.ppm
mpprun ./blurc 16 images/im3.ppm results/averaging/batch3_16.ppm
mpprun ./blurc 16 images/im3.ppm results/averaging/batch3_16.ppm
mpprun ./blurc 16 images/im3.ppm results/averaging/batch3_16.ppm
mpprun ./blurc 16 images/im3.ppm results/averaging/batch3_16.ppm
mpprun ./blurc 16 images/im3.ppm results/averaging/batch3_16.ppm

echo ""
echo "Image 3 - 9 runs radius 32"
echo ""

mpprun ./blurc 32 images/im3.ppm results/averaging/batch3_32.ppm
mpprun ./blurc 32 images/im3.ppm results/averaging/batch3_32.ppm
mpprun ./blurc 32 images/im3.ppm results/averaging/batch3_32.ppm
mpprun ./blurc 32 images/im3.ppm results/averaging/batch3_32.ppm
mpprun ./blurc 32 images/im3.ppm results/averaging/batch3_32.ppm
mpprun ./blurc 32 images/im3.ppm results/averaging/batch3_32.ppm
mpprun ./blurc 32 images/im3.ppm results/averaging/batch3_32.ppm
mpprun ./blurc 32 images/im3.ppm results/averaging/batch3_32.ppm
mpprun ./blurc 32 images/im3.ppm results/averaging/batch3_32.ppm

echo ""
echo "Image 4 - 9 runs radius 4"
echo ""

mpprun ./blurc 4 images/im4.ppm results/averaging/batch4_4.ppm
mpprun ./blurc 4 images/im4.ppm results/averaging/batch4_4.ppm
mpprun ./blurc 4 images/im4.ppm results/averaging/batch4_4.ppm
mpprun ./blurc 4 images/im4.ppm results/averaging/batch4_4.ppm
mpprun ./blurc 4 images/im4.ppm results/averaging/batch4_4.ppm
mpprun ./blurc 4 images/im4.ppm results/averaging/batch4_4.ppm
mpprun ./blurc 4 images/im4.ppm results/averaging/batch4_4.ppm
mpprun ./blurc 4 images/im4.ppm results/averaging/batch4_4.ppm
mpprun ./blurc 4 images/im4.ppm results/averaging/batch4_4.ppm

echo ""
echo "Image 4 - 9 runs radius 8"
echo ""

mpprun ./blurc 8 images/im4.ppm results/averaging/batch4_8.ppm
mpprun ./blurc 8 images/im4.ppm results/averaging/batch4_8.ppm
mpprun ./blurc 8 images/im4.ppm results/averaging/batch4_8.ppm
mpprun ./blurc 8 images/im4.ppm results/averaging/batch4_8.ppm
mpprun ./blurc 8 images/im4.ppm results/averaging/batch4_8.ppm
mpprun ./blurc 8 images/im4.ppm results/averaging/batch4_8.ppm
mpprun ./blurc 8 images/im4.ppm results/averaging/batch4_8.ppm
mpprun ./blurc 8 images/im4.ppm results/averaging/batch4_8.ppm
mpprun ./blurc 8 images/im4.ppm results/averaging/batch4_8.ppm

echo ""
echo "Image 4 - 9 runs radius 16"
echo ""

mpprun ./blurc 16 images/im4.ppm results/averaging/batch4_16.ppm
mpprun ./blurc 16 images/im4.ppm results/averaging/batch4_16.ppm
mpprun ./blurc 16 images/im4.ppm results/averaging/batch4_16.ppm
mpprun ./blurc 16 images/im4.ppm results/averaging/batch4_16.ppm
mpprun ./blurc 16 images/im4.ppm results/averaging/batch4_16.ppm
mpprun ./blurc 16 images/im4.ppm results/averaging/batch4_16.ppm
mpprun ./blurc 16 images/im4.ppm results/averaging/batch4_16.ppm
mpprun ./blurc 16 images/im4.ppm results/averaging/batch4_16.ppm
mpprun ./blurc 16 images/im4.ppm results/averaging/batch4_16.ppm

echo ""
echo "Image 4 - 9 runs radius 32"
echo ""

mpprun ./blurc 32 images/im4.ppm results/averaging/batch4_32.ppm
mpprun ./blurc 32 images/im4.ppm results/averaging/batch4_32.ppm
mpprun ./blurc 32 images/im4.ppm results/averaging/batch4_32.ppm
mpprun ./blurc 32 images/im4.ppm results/averaging/batch4_32.ppm
mpprun ./blurc 32 images/im4.ppm results/averaging/batch4_32.ppm
mpprun ./blurc 32 images/im4.ppm results/averaging/batch4_32.ppm
mpprun ./blurc 32 images/im4.ppm results/averaging/batch4_32.ppm
mpprun ./blurc 32 images/im4.ppm results/averaging/batch4_32.ppm
mpprun ./blurc 32 images/im4.ppm results/averaging/batch4_32.ppm

#
