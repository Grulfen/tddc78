set autoscale
set xlabel "Number of particles (10000)"
set ylabel "Pressure"
set title "Pressure vs n"
set terminal png
set output 'particles.png'

plot "particles.dat" using 1:2 title "p vs n" with linespoints

set xlabel "Max initial velocity"
set ylabel "sqrt(pressure)"
set title "sqrt(Pressure) vs T"
set output 'temperature.png'

plot "temperature.dat" using 1:(sqrt($2)) title "sqrt(p) vs T" with linespoints

set xlabel "1/area (10^-8)"
set ylabel "pressure"
set title "Pressure vs 1/Area"
set output 'area.png'

plot "area.dat" using (1/$1):2 title "p vs 1/area" with linespoints
