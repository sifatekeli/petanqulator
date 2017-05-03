#!/bin/sh
../build/petanqulator_test2.out > out_plot.csv
gnuplot plot.gnu
eog out_plot.png

