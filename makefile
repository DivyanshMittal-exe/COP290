.PHONY: clean
.PHONY: debug
.PHONY: pdebug
.PHONY: debug_all

MKL_BLAS_PATH = /usr/include/mkl

all:
	@echo "Compiling"
	@make run

run: main.o audio.o 
	g++ -I /usr/include/mkl  -O3 -g main.o audio.o -o yourcode.out -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl

audio.o: audio.cpp
	g++ -c -g audio.cpp 

main.o: main.cpp
	@g++ -O3 -c -g main.cpp

lib: audio.cpp
	g++ -I $(MKL_BLAS_PATH) -c -Wall -Werror -fpic audio.cpp -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl
	g++ -shared -o libaudio.so audio.o

compile: main.cpp
	g++ -I $(MKL_BLAS_PATH) -L . -Wl,-rpath=. -Wall -o yourcode.out main.cpp -laudio -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl


debug: clean run
	sh debugger.sh debug

interactive: 
	make run
	./yourcode.out interactive_audio.txt interactive_output.txt

live:
	python interactive.py

clean:
	@rm -rf *.o *.out lib/Plain/*.o lib/pThread/*.o 

