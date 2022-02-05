#include "Matrix.h"
#include <fstream>
#include <math.h>

// Constructor for Matrix class with default file passed

template <typename T>
Matrix<T>::Matrix(const std::string &filename)
{
    std::ifstream input_file(filename);

    if(!input_file.good())
        throw std::runtime_error("File not found. Empty matrix returned");

    input_file >> col;
    input_file >> row;

    std::vector<std::vector<T>> elems(row, std::vector<T>(col, 0));

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            T val;
            input_file >> val;
            elems[j][i] = val;
        }
    }
    elements = elems;
}

// Constructor for Matrix class with no argument to initialise as 0 size matrix

template <typename T>
Matrix<T>::Matrix()
{
    row = 0;
    col = 0;
}
template <typename T>

// Returns element (i,j)
T Matrix<T>::getElement(int i, int j) const 
{
    std::vector<T> row = elements.at(i);
    return row.at(j);
}

//Returns a matrix with relu applied on it

template <typename T>
Matrix<T> Matrix<T>::relu()
{
    Matrix<T> Matrix_return;
    std::vector<std::vector<T>> elem;
    Matrix_return.row = row;
    Matrix_return.col = col;

    for (int r = 0; r < row; r++)
    {
        std::vector<T> col_vec;
        for (int c = 0; c < col; c++)
        {
            T val = getElement(r, c);
            val = val > 0 ? val : 0;
            col_vec.push_back(val);
        }
        elem.push_back(col_vec);
    }
    Matrix_return.elements = elem;

    return Matrix_return;
}

//Returns a matrix with tanh applied on it

template <typename T>
Matrix<T> Matrix<T>::matrix_tanh()
{
    Matrix<T> Matrix_return;
    std::vector<std::vector<T>> elem;
    Matrix_return.row = row;
    Matrix_return.col = col;

    for (int r = 0; r < row; r++)
    {
        std::vector<T> col_vec;
        for (int c = 0; c < col; c++)
        {
            T val = getElement(r, c);
            //Implementation of tanh with exp
            T ex = exp(val);
            T neg_ex = exp(-val);
            val = (ex - neg_ex) / (ex + neg_ex);
            col_vec.push_back(val);
        }
        elem.push_back(col_vec);
    }
    Matrix_return.elements = elem;

    return Matrix_return;
}

// Retuns a matrix with max poolong on it

template <typename T>
Matrix<T> Matrix<T>::max_pooling(int stride)
{
    if(stride ==0)
        throw std::runtime_error("Incompatible stride error \n");
    
    if(row == col)
        throw std::runtime_error("Column and row size are not the same \n");

    if (col % stride != 0)
        throw std::runtime_error("Stride does not divide matrix dimension \n");

    Matrix<T> Matrix_return;
    std::vector<std::vector<T>> elem;
    Matrix_return.row = row / stride;
    Matrix_return.col = col / stride;



    for (int r = 0; r < row; r += stride)
    {
        std::vector<T> col_vec;
        for (int c = 0; c < col; c += stride)
        {
            T val = getElement(r, c);
            for (int i = 0; i < stride; i++)
            {
                for (int j = 0; j < stride; j++)
                {
                    val = std::max(val, getElement(r + i, c + j));
                }
            }
            col_vec.push_back(val);
        }
        elem.push_back(col_vec);
    }
    Matrix_return.elements = elem;

    return Matrix_return;
}

// Retuns a matrix with avg poolong on it

template <typename T>
Matrix<T> Matrix<T>::avg_pooling(int stride)
{

    if(stride ==0)
        throw std::runtime_error("Incompatible stride error \n");
    
    if(row == col)
        throw std::runtime_error("Column and row size are not the same \n");

    if (col % stride != 0)
        throw std::runtime_error("Stride does not divide matrix dimension \n");


    Matrix<T> Matrix_return;
    std::vector<std::vector<T>> elem;
    Matrix_return.row = row / stride;
    Matrix_return.col = col / stride;

   

    for (int r = 0; r < row; r += stride)
    {
        std::vector<T> col_vec;
        for (int c = 0; c < col; c += stride)
        {
            T val = 0.0f;
            for (int i = 0; i < stride; i++)
            {
                for (int j = 0; j < stride; j++)
                {
                    val += getElement(r + i, c + j);
                }
            }
            val /= (stride * stride);
            col_vec.push_back(val);
        }
        elem.push_back(col_vec);
    }
    Matrix_return.elements = elem;

    return Matrix_return;
}

//Funtion to print a matrix to the given stream

template <typename T>
void Matrix<T>::print(const std::string &filename)
{

    std::ofstream output_file(filename);
    output_file << col << std::endl;
    output_file << row << std::endl;

    typename std::vector<std::vector<T>>::iterator r;
    typename std::vector<T>::iterator c;

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            output_file << elements[j][i] << std::endl;
        }
    }
}

//Funtion to overload the * operation for matrix. Multiply 2 matrices of size axb and bxc to get back a axc size matrix
// Raises error if size mismatch
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &Matrix_2)
{
    Matrix<T> Matrix_return;
    std::vector<std::vector<T>> elem;
    try
    {
        if (col != Matrix_2.row)
        {
            throw std::runtime_error("Size Mismatch, the provided matrices are not compatible to perform this funtion \n");
        }
        Matrix_return.row = row;
        Matrix_return.col = Matrix_2.col;

        for (int r = 0; r < row; r++)
        {
            std::vector<T> col_vec;
            for (int c = 0; c < Matrix_2.col; c++)
            {
                T val = 0.0f;
                for (int i = 0; i < col; i++)
                {
                    val += getElement(r, i) * Matrix_2.getElement(i, c);
                }
                col_vec.push_back(val);
            }
            elem.push_back(col_vec);
        }
        Matrix_return.elements = elem;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return Matrix_return;
}

//Funtion to overload the + operation for matrix. Multiply 2 matrices of size axb and axb to get back a axb size matrix
// Raises error if size mismatch
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &Matrix_2)
{
    Matrix<T> Matrix_return;
    std::vector<std::vector<T>> elem;
    try
    {
        if (row != Matrix_2.row || col != Matrix_2.col)
        {
            throw std::runtime_error("Size Mismatch, the provided matrices are not compatible to perform this funtion \n");
        }
        Matrix_return.row = row;
        Matrix_return.col = col;

        for (int r = 0; r < row; r++)
        {
            std::vector<T> col_vec;
            for (int c = 0; c < col; c++)
            {
                T val = getElement(r, c) + Matrix_2.getElement(r, c);
                col_vec.push_back(val);
            }
            elem.push_back(col_vec);
        }
        Matrix_return.elements = elem;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return Matrix_return;
}

