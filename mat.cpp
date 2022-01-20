#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

struct sizeMismatch : public std::exception
{
    const char *what() const throw()
    {
        return "Matrix size mismatch";
    }
};

class Matrix
{
public:
    int row;
    int col;
    vector<vector<float>> elements;

    Matrix() {}
    Matrix(string filename)
    {
        ifstream input_file(filename);
        int r, c;
        input_file >> r;
        input_file >> c;
        row = r;
        col = c;
        vector<vector<float>> elem;

        for (int i = 0; i < r; i++)
        {
            vector<float> col;
            for (int j = 0; j < c; j++)
            {
                float val;
                input_file >> val;
                col.push_back(val);
            }
            elem.push_back(col);
        }
        elements = elem;
    }
    float getElement(int i, int j)
    {
        vector<float> row = elements.at(i);
        return row.at(j);
    }
    Matrix relu()
    {
        Matrix Matrix_return;
        vector<vector<float>> elem;
        Matrix_return.row = row;
        Matrix_return.col = col;

        for (int r = 0; r < row; r++)
        {
            vector<float> col_vec;
            for (int c = 0; c < col; c++)
            {
                float val = getElement(r, c);
                val = val > 0 ? val : 0;
                col_vec.push_back(val);
            }
            elem.push_back(col_vec);
        }
        Matrix_return.elements = elem;

        return Matrix_return;
    }
    Matrix matrix_tanh()
    {
        Matrix Matrix_return;
        vector<vector<float>> elem;
        Matrix_return.row = row;
        Matrix_return.col = col;

        for (int r = 0; r < row; r++)
        {
            vector<float> col_vec;
            for (int c = 0; c < col; c++)
            {
                float val = tanh(getElement(r, c));
                col_vec.push_back(val);
            }
            elem.push_back(col_vec);
        }
        Matrix_return.elements = elem;

        return Matrix_return;
    }
    Matrix max_pooling(int stride)
    {
        Matrix Matrix_return;
        vector<vector<float>> elem;
        Matrix_return.row = row / stride;
        Matrix_return.col = col / stride;

        for (int r = 0; r < row; r += stride)
        {
            vector<float> col_vec;
            for (int c = 0; c < col; c += stride)
            {
                float val = getElement(r, c);
                for (int i = 0; i < stride; i++)
                {
                    for (int j = 0; j < stride; j++)
                    {
                        val = max(val, getElement(r + i, c + j));
                    }
                }
                col_vec.push_back(val);
            }
            elem.push_back(col_vec);
        }
        Matrix_return.elements = elem;

        return Matrix_return;
    }

    Matrix avg_pooling(int stride)
    {
        Matrix Matrix_return;
        vector<vector<float>> elem;
        Matrix_return.row = row / stride;
        Matrix_return.col = col / stride;

        for (int r = 0; r < row; r += stride)
        {
            vector<float> col_vec;
            for (int c = 0; c < col; c += stride)
            {
                float val = 0.0f;
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
};

Matrix operator*(Matrix Matrix_1, Matrix Matrix_2)
{
    Matrix Matrix_return;
    vector<vector<float>> elem;
    try
    {
        if (Matrix_1.col != Matrix_2.row)
        {
            throw sizeMismatch();
        }
        Matrix_return.row = Matrix_1.row;
        Matrix_return.col = Matrix_2.col;

        for (int r = 0; r < Matrix_1.row; r++)
        {
            vector<float> col;
            for (int c = 0; c < Matrix_2.col; c++)
            {
                float val = 0.0f;
                for (int i = 0; i < Matrix_1.col; i++)
                {
                    val += Matrix_1.getElement(r, i) * Matrix_2.getElement(i, c);
                }
                col.push_back(val);
            }
            elem.push_back(col);
        }
        Matrix_return.elements = elem;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return Matrix_return;
}

Matrix operator+(Matrix Matrix_1, Matrix Matrix_2)
{
    Matrix Matrix_return;
    vector<vector<float>> elem;
    try
    {
        if (Matrix_1.row != Matrix_2.row || Matrix_1.col != Matrix_2.col)
        {
            throw sizeMismatch();
        }
        Matrix_return.row = Matrix_1.row;
        Matrix_return.col = Matrix_1.col;

        for (int r = 0; r < Matrix_1.row; r++)
        {
            vector<float> col;
            for (int c = 0; c < Matrix_1.col; c++)
            {
                float val = Matrix_1.getElement(r, c) + Matrix_2.getElement(r, c);
                col.push_back(val);
            }
            elem.push_back(col);
        }
        Matrix_return.elements = elem;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return Matrix_return;
}


class Vector{
    public:
    int size;
    vector<float> elements;
    Vector() {}
    Vector(string filename)
    {
        ifstream input_file(filename);
        int i = 0;
        vector<float> elem;
        float read;

        while (input_file >> read)
        {
            elements.push_back(read);
            i+=1;
        }
        size = i;
    }

    Vector sigmoid(){
        Vector Vector_return;
        Vector_return.size = size;
        for (auto iter = elements.cbegin(); iter != elements.cend(); ++iter)
        {
            float ele = *iter;
            ele = 1 /(1 + exp(-ele));
            Vector_return.elements.push_back(ele);
        }
        return Vector_return;
    }
    Vector softmax(){
        Vector Vector_return;
        Vector_return.size = size;
        float sum = 0;
        for (auto iter = elements.cbegin(); iter != elements.cend(); ++iter)
        {
            float ele = *iter;
            sum += exp(ele);
        }
        for (auto iter = elements.cbegin(); iter != elements.cend(); ++iter)
        {
            float ele = *iter;
            ele = exp(ele)/sum;
            Vector_return.elements.push_back(ele);
        }
        return Vector_return;
    }

};


int main()
{

    return 0;
}