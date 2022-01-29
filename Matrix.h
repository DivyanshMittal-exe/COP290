#include <iostream>
#include <bits/stdc++.h>
#include <exception>

#ifndef _Matrix_H
#define _Matrix_H

class Matrix
{

public:
    int row;
    int col;
    std::vector<std::vector<float>> elements;

    Matrix();
    Matrix(std::string filename);

    float getElement(int i, int j);

    Matrix relu();
    Matrix matrix_tanh();
    Matrix max_pooling(int stride);
    Matrix avg_pooling(int stride);
    void print(std::string filename);

    friend Matrix operator*(Matrix Matrix_1, Matrix Matrix_2);
    friend Matrix operator+(Matrix Matrix_1, Matrix Matrix_2);
};

#endif //_Matrix_H