set out 'out_plot.png'
set terminal png size 1000,600
set grid xtics
set grid ytics
set xlabel 'pitch'
set ylabel 'distanceToJack'
plot 'out_plot.csv' using 2:7 with lines notitle
