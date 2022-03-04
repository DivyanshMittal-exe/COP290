.PHONY: clean
.PHONY: debug
.PHONY: pdebug
.PHONY: debug_all

all:
	@echo "Compiling"
	@make run

run: audio.cpp
	g++ -I /usr/include/mkl audio.cpp -o ./yourcode.out -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl

debug: clean run
	sh debugger.sh debug

clean:
	@rm -rf *.o *.out lib/Plain/*.o lib/pThread/*.o 

