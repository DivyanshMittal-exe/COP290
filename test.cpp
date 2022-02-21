#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>
#include "mkl.h"
using namespace std;

int main(int argc, char *argv[])
{
    double A[6] = {1,2,0,1,2,3};
    double B[6] = {2,0,0,0,1,0};
    double C[4];
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, 2,    2,    3, 1.0,   A,   2, B, 3,  0.0, C,  2);
    cout << C[0];
    cout << C[1];
    cout << C[2];
    cout << C[3];
    return 0;
}