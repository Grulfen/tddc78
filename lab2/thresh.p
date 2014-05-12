set autoscale
set xlabel "Number of threads"
set ylabel "Average execution time"
set terminal png
set output 'threshold.png'

plot "result/threshold/result.dat" using 1:2 title "Image 1" with linespoints, \
     "result/threshold/result.dat" using 1:3 title "Image 2" with linespoints, \
     "result/threshold/result.dat" using 1:4 title "Image 3" with linespoints, \
     "result/threshold/result.dat" using 1:5 title "Image 4" with linespoints  
