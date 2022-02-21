.PHONY: clean
.PHONY: debug

all:
	@echo "Compiling"
	@make run

run: main.o ./lib/Plain/Matrix.o ./lib/Plain/Vector.o ./lib/pThread/pMatrix.o
	g++ -O3 -g -pthread main.o lib/Plain/Matrix.o lib/Plain/Vector.o lib/pThread/pMatrix.o -o yourcode.out

main.o: main.cpp
	@g++ -O3 -c -g main.cpp

Plain/Matrix.o: lib/Plain/Matrix.cpp
	@g++ -O3 -c -g ./lib/Plain/Matrix.cpp

pThread/pMatrix.o: lib/pThread/pMatrix.cpp
	@g++ -O3 -c -g -pthread ./lib/pThread/pMatrix.cpp

Plain/Vector.o: lib/Plain/Vector.cpp
	@g++ -O3 -c -g ./lib/Plain/Vector.cpp

mkl: mklFC.cpp
	g++ -I /usr/include/mkl mklFC.cpp -o ./yourcode.out -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl

oblas: oblasFC.cpp
	g++ -I/opt/OpenBLAS/include -o yourcode.out oblasFC.cpp  -L/opt/OpenBLAS/lib -lopenblas -lpthread -lgfortran

debug: clean run
	sh debugger.sh debug

pdebug: clean run
	sh debugger.sh pdebug

clean:
	@rm -rf *.o *.out lib/Plain/*.o lib/pThread/*.o 

