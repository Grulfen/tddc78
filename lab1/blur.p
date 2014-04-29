set autoscale
set xlabel "Number of processes"
set ylabel "Average execution time"
set logscale y
set title "Radius 4"
set terminal png
set output 'blur_4.png'

plot "result/blur/result_4.dat" using 1:2 title "Image 1" with linespoints, \
     "result/blur/result_4.dat" using 1:3 title "Image 2" with linespoints, \
     "result/blur/result_4.dat" using 1:4 title "Image 3" with linespoints, \
     "result/blur/result_4.dat" using 1:5 title "Image 4" with linespoints  

set title "Radius 8"
set output 'blur_8.png'

plot "result/blur/result_8.dat" using 1:2 title "Image 1" with linespoints, \
     "result/blur/result_8.dat" using 1:3 title "Image 2" with linespoints, \
     "result/blur/result_8.dat" using 1:4 title "Image 3" with linespoints, \
     "result/blur/result_8.dat" using 1:5 title "Image 4" with linespoints  

set title "Radius 16"
set output 'blur_16.png'

plot "result/blur/result_16.dat" using 1:2 title "Image 1" with linespoints, \
     "result/blur/result_16.dat" using 1:3 title "Image 2" with linespoints, \
     "result/blur/result_16.dat" using 1:4 title "Image 3" with linespoints, \
     "result/blur/result_16.dat" using 1:5 title "Image 4" with linespoints  

set title "Radius 32"
set output 'blur_32.png'

plot "result/blur/result_32.dat" using 1:2 title "Image 1" with linespoints, \
     "result/blur/result_32.dat" using 1:3 title "Image 2" with linespoints, \
     "result/blur/result_32.dat" using 1:4 title "Image 3" with linespoints, \
     "result/blur/result_32.dat" using 1:5 title "Image 4" with linespoints  
