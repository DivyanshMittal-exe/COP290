 set style fill solid 0.25 border -1
 set style boxplot outliers pointtype 0
 set style data boxplot
 set terminal png
 set output "graph.png"
#  set yrange[0:0.004]
set xtics('Plain' 1, 'PThread' 2, 'MKL' 3, 'OpenBLAS' 4)
set xlabel('Implementations')
set ylabel('Run-time(in ms)')
set title('Run-times for 100x100 matrix')


plot 'data/plain.dat' using(1):1 notitle, \
      'data/pthread.dat' using(2):1 notitle, \
      'data/mkl.dat' using(3):1 notitle, \
      'data/oblas.dat' using(4):1 notitle