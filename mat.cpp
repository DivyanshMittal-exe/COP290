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

class mat
{
public:
    int row;
    int col;
    vector<vector<float>> elements;

    mat() {}
    mat(string filename)
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
    mat relu()
    {
        mat ret;
        vector<vector<float>> elem;
        ret.row = row;
        ret.col = col;

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
        ret.elements = elem;

        return ret;
    }
    mat mat_tanh()
    {
        mat ret;
        vector<vector<float>> elem;
        ret.row = row;
        ret.col = col;

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
        ret.elements = elem;

        return ret;
    }
    mat max_pooling(int stride)
    {
        mat ret;
        vector<vector<float>> elem;
        ret.row = row / stride;
        ret.col = col / stride;

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
        ret.elements = elem;

        return ret;
    }

    mat avg_pooling(mat m1, int stride)
    {
        mat ret;
        vector<vector<float>> elem;
        ret.row = row / stride;
        ret.col = col / stride;

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
        ret.elements = elem;

        return ret;
    }
};

mat operator*(mat m1, mat m2)
{
    mat ret;
    vector<vector<float>> elem;
    try
    {
        if (m1.col != m2.row)
        {
            throw sizeMismatch();
        }
        ret.row = m1.row;
        ret.col = m2.col;

        for (int r = 0; r < m1.row; r++)
        {
            vector<float> col;
            for (int c = 0; c < m2.col; c++)
            {
                float val = 0.0f;
                for (int i = 0; i < m1.col; i++)
                {
                    val += m1.getElement(r, i) * m2.getElement(i, c);
                }
                col.push_back(val);
            }
            elem.push_back(col);
        }
        ret.elements = elem;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return ret;
}

mat operator+(mat m1, mat m2)
{
    mat ret;
    vector<vector<float>> elem;
    try
    {
        if (m1.row != m2.row || m1.col != m2.col)
        {
            throw sizeMismatch();
        }
        ret.row = m1.row;
        ret.col = m1.col;

        for (int r = 0; r < m1.row; r++)
        {
            vector<float> col;
            for (int c = 0; c < m1.col; c++)
            {
                float val = m1.getElement(r, c) + m2.getElement(r, c);
                col.push_back(val);
            }
            elem.push_back(col);
        }
        ret.elements = elem;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return ret;
}

int main()
{

    return 0;
}