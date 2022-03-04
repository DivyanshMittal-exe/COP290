.PHONY: clean
.PHONY: debug
.PHONY: pdebug
.PHONY: debug_all

all:
	@echo "Compiling"
	@make run

run: audio.o libaudio.o 
	g++ -O3 -g audio.o libaudio.o -o yourcode.out

libaudio.o: libaudio.cpp
	g++ -I /usr/include/mkl -c -g libaudio.cpp -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl

audio.o: audio.cpp
	@g++ -O3 -c -g audio.cpp


debug: clean run
	sh debugger.sh debug

clean:
	@rm -rf *.o *.out lib/Plain/*.o lib/pThread/*.o 

