#include <iostream>
#include <exception>
#include <string>

#ifndef _oBMatrix_H
#define _oBMatrix_H


template<typename T>

class oBMatrix
{

public:
    int row;
    int col;
    T elements[row*col];

    oBMatrix();
    oBMatrix(int row,int col);
    oBMatrix(const std::string &filename);

    oBMatrix<T> transpose() const;


    T getElement (int i, int j) const;

    oBMatrix<T> relu();
    oBMatrix<T> oBMatrix_tanh();
    oBMatrix<T> max_pooling(int stride);
    oBMatrix<T> avg_pooling(int stride);
    void print(const std::string &filename);
    // oBMatrix<T> operator*(const oBMatrix<T> &oBMatrix_2);
    // oBMatrix<T> operator+(const oBMatrix<T> &oBMatrix_2);
};

template class oBMatrix<float>;
template class oBMatrix<double>;
template class oBMatrix<int>;


#endif //_oBMatrix_H