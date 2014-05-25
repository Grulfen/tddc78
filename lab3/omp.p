set autoscale
set xlabel "Number of threads"
set ylabel "Average execution time"
set terminal png
set output 'omp.png'

plot "result.dat" using 1:2 title "16 cores" with linespoints
