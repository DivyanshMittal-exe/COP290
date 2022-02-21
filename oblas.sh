g++ -I/opt/OpenBLAS/include -o yourcode.out oblasFC.cpp  -L/opt/OpenBLAS/lib -lopenblas -lpthread -lgfortran

./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt test_outputmatrix.txt


