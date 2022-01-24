.PHONY: clean

all:
	@echo "Compiling"
	@make run

run: main.o Matrix.o Vector.o
	@g++ main.o Matrix.o Vector.o -o main
	@./main

main.o: main.cpp
	@g++ -c main.cpp

Matrix.o: Matrix.cpp
	@g++ -c Matrix.cpp

Vector.o: Vector.cpp
	@g++ -c Vector.cpp

clean:
	@rm -f *.o main