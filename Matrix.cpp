#include "Matrix.h"
#include <fstream>
#include <math.h>

template <typename T>

Matrix<T>::Matrix(const std::string &filename)
{
    std::ifstream input_file(filename);
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
template <typename T>

Matrix<T>::Matrix()
{
    row = 0;
    col = 0;
}
template <typename T>

T Matrix<T>::getElement(int i, int j) const 
{
    std::vector<T> row = elements.at(i);
    return row.at(j);
}
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
template <typename T>

Matrix<T> Matrix<T>::max_pooling(int stride)
{
    Matrix<T> Matrix_return;
    std::vector<std::vector<T>> elem;
    Matrix_return.row = row / stride;
    Matrix_return.col = col / stride;

    if (col % stride != 0)
        throw std::runtime_error("Stride does not divide column dimension \n");

    if (row % stride != 0)
        throw std::runtime_error("Stride does not divide row dimension \n");

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
template <typename T>

Matrix<T> Matrix<T>::avg_pooling(int stride)
{
    Matrix<T> Matrix_return;
    std::vector<std::vector<T>> elem;
    Matrix_return.row = row / stride;
    Matrix_return.col = col / stride;

    if (col % stride != 0)
        throw std::runtime_error("Stride does not divide column dimension \n");

    if (row % stride != 0)
        throw std::runtime_error("Stride does not divide row dimension \n");

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

