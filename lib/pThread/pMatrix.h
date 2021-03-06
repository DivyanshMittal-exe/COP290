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

    pMatrix():Matrix<float>(){};
    pMatrix(int row,int col):Matrix<float>(row,col){};
    pMatrix(const std::string &filename):Matrix<float>(filename){};

    pMatrix transpose() const;

};
    pMatrix fc(const pMatrix &Matrix_1,const pMatrix &Matrix_2,const pMatrix &Matrix_3);


#endif //_pMatrix_H