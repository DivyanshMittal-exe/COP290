#include <iostream>
#include <exception>
#include <vector>
#include <string>

#ifndef _Matrix_H
#define _Matrix_H


template<typename T>

class Matrix
{

public:
    int row;
    int col;
    std::vector<std::vector<T>> elements;

    Matrix();
    Matrix(int row,int col);
    Matrix(const std::string &filename);

    Matrix<T> transpose() const;


    T getElement (int i, int j) const;

    Matrix<T> relu();
    Matrix<T> matrix_tanh();
    Matrix<T> max_pooling(int stride);
    Matrix<T> avg_pooling(int stride);
    void print(const std::string &filename);
    Matrix<T> operator*(const Matrix<T> &Matrix_2);
    Matrix<T> operator+(const Matrix<T> &Matrix_2);
};

template class Matrix<float>;
template class Matrix<double>;
template class Matrix<int>;


#endif //_Matrix_H