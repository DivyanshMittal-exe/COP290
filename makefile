.PHONY: clean
.PHONY: debug

all:
	@echo "Compiling"
	@make run

run: main.o ./lib/Plain/Matrix.o ./lib/Plain/Vector.o ./lib/pThread/pMatrix.o
	@g++ -O3 -pthread main.o lib/Plain/Matrix.o lib/Plain/Vector.o lib/pThread/pMatrix.o -o yourcode.out

main.o: main.cpp
	@g++ -c -O3 main.cpp

Plain/Matrix.o: lib/Plain/Matrix.cpp
	@g++ -c -O3 ./lib/Plain/Matrix.cpp

pThread/pMatrix.o: lib/pThread/pMatrix.cpp
	@g++ -c -O3 -pthread ./lib/pThread/pMatrix.cpp

Plain/Vector.o: lib/Plain/Vector.cpp
	@g++ -c -O3 ./lib/Plain/Vector.cpp

mkl: mklFC.cpp
	g++ -I /usr/include/mkl mklFC.cpp -o ./file.out -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl

debug: clean run
	sh run.sh

clean:
	@rm -rf *.o *.out lib/Plain/*.o lib/pThread/*.o

