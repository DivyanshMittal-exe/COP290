
#include <iostream>
#include <bits/stdc++.h>
#include <exception>


#ifndef _Vector_H
#define _Vector_H

class Vector
{
public:
    int size;
    std::vector<float> elements;

    Vector();
    Vector(std::string filename);

    Vector sigmoid();
    Vector softmax();
    void print(std::string filename);
};

#endif //_Vector_H
