#include <iostream>
#include <exception>
#include <vector>
#include <string>

#ifndef _pMatrix_H
#define _pMatrix_H



class pMatrix
{

public:
    int row;
    int col;
    std::vector<std::vector<float>> elements;

    pMatrix();
    pMatrix(int row,int col);
    pMatrix(const std::string &filename);

    pMatrix transpose() const;

    float* getElement (int i, int j) const;

    void print(const std::string &filename);
    pMatrix operator*(const pMatrix &Matrix_2);
    pMatrix operator+(const pMatrix &Matrix_2);
};

// template class pMatrix<float>;
// template class pMatrix<double>;
// template class pMatrix<int>;


#endif //_pMatrix_H