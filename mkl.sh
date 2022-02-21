g++ -I /usr/include/mkl mklFC.cpp -o ./yourcode.out -fopenmp -lmkl_intel_lp64 -lmkl_core -lmkl_gnu_thread -lpthread -lm -ldl

./yourcode.out fullyconnectedrun inputmatrix.txt weightmatrix.txt biasmatrix.txt test_outputmatrix.txt