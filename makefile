.PHONY: clean
.PHONY: debug

all:
	@echo "Compiling"
	@make run

run: main.o Plain/Matrix.o Plain/Vector.o pThread/pMatrix.o
	@g++ -O3  main.o Plain/Matrix.o Plain/Vector.o pThread/pMatrix.o -o yourcode.out

main.o: main.cpp
	@g++ -c -O3 main.cpp

Plain/Matrix.o: Plain/Matrix.cpp
	@g++ -c -O3 Plain/Matrix.cpp

pThread/pMatrix.o: pThread/pMatrix.cpp
	@g++ -c -O3 -pthreads pThread/pMatrix.cpp

Plain/Vector.o: Plain/Vector.cpp
	@g++ -c -O3 Plain/Vector.cpp

debug: clean run
	sh run.sh

clean:
	@rm -f *.o *.out 

