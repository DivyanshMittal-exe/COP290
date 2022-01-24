#include "Matrix.h"

using namespace std;

const char * sizeMismatch::what () const throw ()
    {
    	return "Size Incompatible";
    }

Matrix::Matrix(string filename)
    {
        ifstream input_file(filename);
        int r=0, c=0;
        float read;

        while (input_file >> read)
        {   
            r++;
            if(input_file.peek() == '\n'){
                break;
            }
        }
        vector<vector<float>> elem(r);

        input_file.seekg(0);
        vector< vector<float> >::iterator col_it;
        col_it = elem.begin();
        while (input_file >> read)
        {   
            col_it->push_back(read);
            col_it++;
            if(input_file.peek() == '\n'){
                col_it = elem.begin();
                c++;
            }
        }
        row = r;
        col = c;

    }

Matrix::Matrix(){
    row = 0;
    col = 0;
}

float Matrix::getElement(int i, int j)
    {
        vector<float> row = elements.at(i);
        return row.at(j);
    }

Matrix Matrix::relu()
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




Matrix Matrix::matrix_tanh()
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

Matrix Matrix::max_pooling(int stride)
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

Matrix Matrix::avg_pooling(int stride)
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


void Matrix:: print(){
    vector< vector<float> >::iterator r;
    vector<float>::iterator c;

    for (r = elements.begin(); r != elements.end(); r++) {
        for (c = r->begin(); c != r->end(); c++) {
            cout << *c << " ";
        }
        cout << endl;
    }
}


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
