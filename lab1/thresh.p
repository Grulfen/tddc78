set autoscale
set xlabel "Processes"
set ylabel "Average execution time"
set terminal png
set output 'threshold.png'

plot "result/thres/result.dat" using 1:2 title "Image 1" with linespoints, \
     "result/thres/result.dat" using 1:3 title "Image 2" with linespoints, \
     "result/thres/result.dat" using 1:4 title "Image 3" with linespoints, \
     "result/thres/result.dat" using 1:5 title "Image 4" with linespoints  
