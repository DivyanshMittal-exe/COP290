.PHONY: clean
.PHONY: debug
.PHONY: pdebug
.PHONY: debug_all

all:
	@echo "Compiling"
	@make run

run: audio.o libaudio.o 
	g++ -I /usr/include/mkl  -O3 -g audio.o libaudio.o -o yourcode.out -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl

libaudio.o: libaudio.cpp
	g++ -c -g libaudio.cpp 

audio.o: audio.cpp
	@g++ -O3 -c -g audio.cpp

lib: libaudio.cpp
	g++ -I /usr/include/mkl -c -Wall -Werror -fpic libaudio.cpp -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl
	g++ -shared -o liblibaudio.so libaudio.o

test: audio.cpp
	g++ -I /usr/include/mkl -L . -Wall -o yourcode.out audio.cpp -llibaudio -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl


debug: clean run
	sh debugger.sh debug

interactive: 
	make run
	./yourcode.out interactive_audio.txt interactive_output.txt

live:
	python interactive.py

clean:
	@rm -rf *.o *.out lib/Plain/*.o lib/pThread/*.o 

