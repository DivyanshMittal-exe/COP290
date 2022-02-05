#include <iostream>
#include <vector>
#include <exception>
#include <string>


#ifndef _Vector_H
#define _Vector_H

template<typename T>
class Vector
{
public:
    int size;
    std::vector<T> elements;

    Vector();
    Vector(const std::string &filename);

    Vector<T> sigmoid();
    Vector<T> softmax();
    void print(const std::string &filename);
};

template class Vector<float>;
template class Vector<double>;
template class Vector<int>;

#endif //_Vector_H
