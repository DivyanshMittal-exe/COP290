.PHONY: clean

all:
	@echo "Compiling"
	@make run

run: main.o Matrix.o Vector.o
	@g++ -g  main.o Matrix.o Vector.o -o yourcode.out

main.o: main.cpp
	@g++ -c main.cpp

Matrix.o: Matrix.cpp
	@g++ -c Matrix.cpp

Vector.o: Vector.cpp
	@g++ -c Vector.cpp

debug: clean run
	sh run.sh

clean:
	@rm -f *.o *.out main

