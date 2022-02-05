#include <iostream>
#include <exception>
#include <vector>
#include <string>

#ifndef _pMatrix_H
#define _pMatrix_H


template<typename T>

class pMatrix
{

public:
    int row;
    int col;
    std::vector<std::vector<T>> elements;

    pMatrix();
    pMatrix(int row,int col);
    pMatrix(const std::string &filename);

    T* getElement (int i, int j) const;

    pMatrix<T> relu();
    pMatrix<T> matrix_tanh();
    pMatrix<T> transpose();
    pMatrix<T> max_pooling(int stride);
    pMatrix<T> avg_pooling(int stride);
    void print(const std::string &filename);
    pMatrix<T> operator*(const pMatrix<T> &Matrix_2);
    pMatrix<T> operator+(const pMatrix<T> &Matrix_2);
};

template class pMatrix<float>;
template class pMatrix<double>;
template class pMatrix<int>;


#endif //_pMatrix_H