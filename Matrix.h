#include <iostream>
#include <bits/stdc++.h>
#include <exception>

using namespace std;

#ifndef _Matrix_H
#define _Matrix_H

struct sizeMismatch : public std::exception
{
	const char * what () const throw ();

};

class Matrix
{

public:

    int row;
    int col;
    vector<vector<float>> elements;


    Matrix();
    Matrix(string filename);

    float getElement(int i, int j);

    Matrix relu();
    Matrix matrix_tanh();
    Matrix max_pooling(int stride);
    Matrix avg_pooling(int stride);
    void print(string filename);

    friend Matrix operator*(Matrix Matrix_1, Matrix Matrix_2);
    friend Matrix operator+(Matrix Matrix_1, Matrix Matrix_2);
    
};

#endif //_Matrix_H