.PHONY: clean
.PHONY: debug

all:
	@echo "Compiling"
	@make run

run: main.o Matrix.o Vector.o
	@g++ -O3  main.o Matrix.o Vector.o -o yourcode.out

main.o: main.cpp
	@g++ -c -O3 main.cpp

Matrix.o: Matrix.cpp
	@g++ -c -O3 Matrix.cpp

Vector.o: Vector.cpp
	@g++ -c -O3 Vector.cpp

debug: clean run
	sh run.sh

clean:
	@rm -f *.o *.out 

