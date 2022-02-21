#png
set style fill solid 0.25 border -1
set style boxplot outliers pointtype 0
set style data boxplot
set terminal png
set output "graph100.png"
#  set yrange[0:0.004]
set xtics('Plain' 1, 'PThread' 2, 'MKL' 3, 'OpenBLAS' 4)
set xlabel('Implementations')
set ylabel('Run-time(in ms)')
set title('Run-times for 100x100 matrix')

plot 'data/plain100.dat' using(1):1 notitle, \
      'data/pthread100.dat' using(2):1 notitle, \
      'data/mkl100.dat' using(3):1 notitle, \
      'data/oblas100.dat' using(4):1 notitle

set style fill solid 0.25 border -1
set style boxplot outliers pointtype 0
set style data boxplot
set terminal png
set output "graph200.png"
#  set yrange[0:0.004]
set xtics('Plain' 1, 'PThread' 2, 'MKL' 3, 'OpenBLAS' 4)
set xlabel('Implementations')
set ylabel('Run-time(in ms)')
set title('Run-times for 200x200 matrix')

plot 'data/plain200.dat' using(1):1 notitle, \
      'data/pthread200.dat' using(2):1 notitle, \
      'data/mkl200.dat' using(3):1 notitle, \
      'data/oblas200.dat' using(4):1 notitle

set style fill solid 0.25 border -1
set style boxplot outliers pointtype 0
set style data boxplot
set terminal png
set output "graph300.png"
#  set yrange[0:0.004]
set xtics('Plain' 1, 'PThread' 2, 'MKL' 3, 'OpenBLAS' 4)
set xlabel('Implementations')
set ylabel('Run-time(in ms)')
set title('Run-times for 300x300 matrix')

plot 'data/plain300.dat' using(1):1 notitle, \
      'data/pthread300.dat' using(2):1 notitle, \
      'data/mkl300.dat' using(3):1 notitle, \
      'data/oblas300.dat' using(4):1 notitle

#eps
set style fill solid 0.25 border -1
set style boxplot outliers pointtype 0
set style data boxplot
set terminal eps
set output "graph100.eps"
#  set yrange[0:0.004]
set xtics('Plain' 1, 'PThread' 2, 'MKL' 3, 'OpenBLAS' 4)
set xlabel('Implementations')
set ylabel('Run-time(in ms)')
set title('Run-times for 100x100 matrix')

plot 'data/plain100.dat' using(1):1 notitle, \
      'data/pthread100.dat' using(2):1 notitle, \
      'data/mkl100.dat' using(3):1 notitle, \
      'data/oblas100.dat' using(4):1 notitle

set style fill solid 0.25 border -1
set style boxplot outliers pointtype 0
set style data boxplot
set terminal eps
set output "graph200.eps"
#  set yrange[0:0.004]
set xtics('Plain' 1, 'PThread' 2, 'MKL' 3, 'OpenBLAS' 4)
set xlabel('Implementations')
set ylabel('Run-time(in ms)')
set title('Run-times for 200x200 matrix')

plot 'data/plain200.dat' using(1):1 notitle, \
      'data/pthread200.dat' using(2):1 notitle, \
      'data/mkl200.dat' using(3):1 notitle, \
      'data/oblas200.dat' using(4):1 notitle

set style fill solid 0.25 border -1
set style boxplot outliers pointtype 0
set style data boxplot
set terminal eps
set output "graph300.eps"
#  set yrange[0:0.004]
set xtics('Plain' 1, 'PThread' 2, 'MKL' 3, 'OpenBLAS' 4)
set xlabel('Implementations')
set ylabel('Run-time(in ms)')
set title('Run-times for 300x300 matrix')

plot 'data/plain300.dat' using(1):1 notitle, \
      'data/pthread300.dat' using(2):1 notitle, \
      'data/mkl300.dat' using(3):1 notitle, \
      'data/oblas300.dat' using(4):1 notitle