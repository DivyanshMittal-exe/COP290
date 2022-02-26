#include "oBMatrix.h"
#include <fstream>
#include <math.h>
#include <cblas.h>

// Constructor for oBMatrix class with default file passed

template <typename T>
oBMatrix<T>::oBMatrix(const std::string &filename)
{
    std::ifstream input_file(filename);

    if(!input_file.good())
        throw std::runtime_error("File not found. Empty Matrix returned");

    input_file >> col;
    input_file >> row;

    T elems[col*row];

    for (int i = 0; i < col*row; i++)
    {
        input_file >> elems[i];
    }
    elements = elems;
}

// Constructor for oBMatrix class with no argument to initialise as 0 size oBMatrix

template <typename T>
oBMatrix<T>::oBMatrix()
{
    row = 0;
    col = 0;
}

template <typename T>
oBMatrix<T>::oBMatrix(int r, int c)
{
    row = r;
    col = c;
    T elems[row*col] = {0};
    elements = elems;
}

template <typename T>
// Returns element (i,j)
inline T oBMatrix<T>::getElement(int i,int j) const 
{
    return elements[row * j + i];
}

template <typename T>
oBMatrix<T> oBMatrix<T>::transpose() const
{
    oBMatrix<T> oBMatrix_return(col, row);
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            oBMatrix_return.elements[row * c + r] = elements[col * r + c];
        }
    }
    return oBMatrix_return;
}

//Returns a oBMatrix with relu applied on it

template <typename T>
oBMatrix<T> oBMatrix<T>::relu()
{
    oBMatrix<T> oBMatrix_return;
    T elem[col*row];
    oBMatrix_return.row = row;
    oBMatrix_return.col = col;

    for (int i = 0; i < row * col; i++)
    {
        T val = elements[i];
        val = val > 0 ? val : 0;
        elem[i] = val;
    }
    oBMatrix_return.elements = elem;

    return oBMatrix_return;
}

//Returns a oBMatrix with tanh applied on it

template <typename T>
oBMatrix<T> oBMatrix<T>::oBMatrix_tanh()
{
    oBMatrix<T> oBMatrix_return;
    T elem[col*row];
    oBMatrix_return.row = row;
    oBMatrix_return.col = col;

    for (int i = 0; i < row * col; i++)
    {
        T val = elements[i];
        //Implementation of tanh with exp
        val = (exp(2 * val) - 1) / (exp(2 * val) + 1);
        elem[i] = val;
    }
    oBMatrix_return.elements = elem;

    return oBMatrix_return;
}

// Retuns a oBMatrix with max poolong on it

template <typename T>
oBMatrix<T> oBMatrix<T>::max_pooling(int stride)
{
    if(stride ==0)
        throw std::runtime_error("Incompatible stride error \n");
    
    if(row != col)
        throw std::runtime_error("Column and row size are not the same \n");

    if (col % stride != 0)
        throw std::runtime_error("Stride does not divide oBMatrix dimension \n");

    oBMatrix<T> oBMatrix_return;
    T elem[(row / stride) * (col / stride)];
    oBMatrix_return.row = row / stride;
    oBMatrix_return.col = col / stride;



    for (int r = 0; r < row; r += stride)
    {
        for (int c = 0; c < col; c += stride)
        {
            T val = elements[c * row + r];
            for (int i = 0; i < stride; i++)
            {
                for (int j = 0; j < stride; j++)
                {
                    val = std::max(val, elements[(c + j) * row + (r + i)]);
                }
            }
            elem[(c / stride)*(row / stride) + (r / stride)] = val;
        }
    }
    oBMatrix_return.elements = elem;

    return oBMatrix_return;
}

// Retuns a oBMatrix with avg poolong on it

template <typename T>
oBMatrix<T> oBMatrix<T>::avg_pooling(int stride)
{

    if(stride ==0)
        throw std::runtime_error("Incompatible stride error \n");
    
    if(row != col)
        throw std::runtime_error("Column and row size are not the same \n");

    if (col % stride != 0)
        throw std::runtime_error("Stride does not divide oBMatrix dimension \n");


    oBMatrix<T> oBMatrix_return;
    T elem[(row / stride) * (col / stride)];
    oBMatrix_return.row = row / stride;
    oBMatrix_return.col = col / stride;

   

    for (int r = 0; r < row; r += stride)
    {
        for (int c = 0; c < col; c += stride)
        {
            T val = 0.0f;
            for (int i = 0; i < stride; i++)
            {
                for (int j = 0; j < stride; j++)
                {
                    val += elements[(c + j) * row + (r + i)];
                }
            }
            val /= (stride * stride);
            elem[(c / stride)*(row / stride) + (r / stride)] = val;
        }
    }
    oBMatrix_return.elements = elem;

    return oBMatrix_return;
}

//Funtion to print a oBMatrix to the given stream

template <typename T>
void oBMatrix<T>::print(const std::string &filename)
{

    std::ofstream output_file(filename);
    output_file << col << std::endl;
    output_file << row << std::endl;

    for (int i = 0; i < row * col; i++)
    {
        output_file << elements[i] << std::endl;
    }
}

