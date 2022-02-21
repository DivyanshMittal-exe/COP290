#include <iostream>
#include <exception>
#include <vector>
#include <string>
#include "../Plain/Matrix.h"

#ifndef _pMatrix_H
#define _pMatrix_H


class pMatrix:public Matrix<float>
{

public:
    // int row;
    // int col;
    // std::vector<std::vector<float>> elements;

    pMatrix():Matrix<float>(){};
    pMatrix(int row,int col):Matrix<float>(row,col){};
    pMatrix(const std::string &filename):Matrix<float>(filename){};

    pMatrix transpose() const;

    // float* getElement (int i, int j) const;

    // void print(const std::string &filename);
    pMatrix operator*(const pMatrix &Matrix_2);
    pMatrix operator+(const pMatrix &Matrix_2);
};



#endif //_pMatrix_H