#include "Vector.h"
#include <fstream>
#include <math.h>

template<typename T>
Vector<T>::Vector()
{
    size = 0;
}

template<typename T>

Vector<T>::Vector(const std::string &filename)
{
    std::ifstream input_file(filename);
    input_file >> size;
    std::vector<T> elems(size, 0);

    for (int i = 0; i < size; i++)
    {
        T val;
        input_file >> val;
        elems[i] = val;
    }
    elements = elems;
}

template<typename T>

Vector<T> Vector<T>::sigmoid()
{
    Vector<T> Vector_return;
    Vector_return.size = size;
    for (auto iter = elements.cbegin(); iter != elements.cend(); ++iter)
    {
        T ele = *iter;
        ele = 1 / (1 + exp(-ele));
        Vector_return.elements.push_back(ele);
    }
    return Vector_return;
}

template<typename T>

Vector<T> Vector<T>::softmax()
{
    Vector<T> Vector_return;
    Vector_return.size = size;
    T sum = 0;
    for (auto iter = elements.cbegin(); iter != elements.cend(); ++iter)
    {
        T ele = *iter;
        sum += exp(ele);
    }
    for (auto iter = elements.cbegin(); iter != elements.cend(); ++iter)
    {
        T ele = *iter;
        T el = exp(ele) / sum;
        Vector_return.elements.push_back(el);
    }
    return Vector_return;
}


template<typename T>
void Vector<T>::print(const std::string &filename)
{
    std::ofstream output_file(filename);
    output_file << size << std::endl;
    for (int i = 0; i < size; i++)
    {
        output_file << elements[i] << std::endl;
    }
}
