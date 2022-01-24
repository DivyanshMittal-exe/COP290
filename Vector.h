
#include <iostream>
#include <bits/stdc++.h>
#include <exception>

using namespace std;

#ifndef _Vector_H
#define _Vector_H

class Vector{
    public:
        int size;
        vector<float> elements;


    Vector();
    Vector(string filename);

    Vector sigmoid();
    Vector softmax();
    void print();
};

#endif //_Vector_H
