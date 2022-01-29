#include "Matrix.h"

Matrix::Matrix(std::string filename)
{
    std::ifstream input_file(filename);
    input_file >> col;
    input_file >> row;

    std::vector<std::vector<float>> elems(row, std::vector<float>(col, 0));

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            float val;
            input_file >> val;
            elems[j][i] = val;
        }
    }
    elements = elems;
}

Matrix::Matrix()
{
    row = 0;
    col = 0;
}

float Matrix::getElement(int i, int j)
{
    std::vector<float> row = elements.at(i);
    return row.at(j);
}

Matrix Matrix::relu()
{
    Matrix Matrix_return;
    std::vector<std::vector<float>> elem;
    Matrix_return.row = row;
    Matrix_return.col = col;

    for (int r = 0; r < row; r++)
    {
        std::vector<float> col_vec;
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
    std::vector<std::vector<float>> elem;
    Matrix_return.row = row;
    Matrix_return.col = col;

    for (int r = 0; r < row; r++)
    {
        std::vector<float> col_vec;
        for (int c = 0; c < col; c++)
        {
            float val = getElement(r, c);
            float ex = exp(val);
            float neg_ex = exp(-val);
            val = (ex - neg_ex) / (ex + neg_ex);
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
    std::vector<std::vector<float>> elem;
    Matrix_return.row = row / stride;
    Matrix_return.col = col / stride;

    if (col % stride != 0)
        throw std::runtime_error("Stride does not divide column dimension \n");

    if (row % stride != 0)
        throw std::runtime_error("Stride does not divide row dimension \n");

    for (int r = 0; r < row; r += stride)
    {
        std::vector<float> col_vec;
        for (int c = 0; c < col; c += stride)
        {
            float val = getElement(r, c);
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

Matrix Matrix::avg_pooling(int stride)
{
    Matrix Matrix_return;
    std::vector<std::vector<float>> elem;
    Matrix_return.row = row / stride;
    Matrix_return.col = col / stride;

    if (col % stride != 0)
        throw std::runtime_error("Stride does not divide column dimension \n");

    if (row % stride != 0)
        throw std::runtime_error("Stride does not divide row dimension \n");

    for (int r = 0; r < row; r += stride)
    {
        std::vector<float> col_vec;
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

void Matrix::print(std::string filename)
{

    std::ofstream output_file(filename);
    output_file << col << std::endl;
    output_file << row << std::endl;

    std::vector<std::vector<float>>::iterator r;
    std::vector<float>::iterator c;

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            output_file << elements[j][i] << std::endl;
        }
    }
}

Matrix operator*(Matrix Matrix_1, Matrix Matrix_2)
{
    Matrix Matrix_return;
    std::vector<std::vector<float>> elem;
    try
    {
        if (Matrix_1.col != Matrix_2.row)
        {
            throw std::runtime_error("Size Mismatch, the provided matrices are not compatible to perform this funtion \n");
        }
        Matrix_return.row = Matrix_1.row;
        Matrix_return.col = Matrix_2.col;

        for (int r = 0; r < Matrix_1.row; r++)
        {
            std::vector<float> col;
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
    std::vector<std::vector<float>> elem;
    try
    {
        if (Matrix_1.row != Matrix_2.row || Matrix_1.col != Matrix_2.col)
        {
            throw std::runtime_error("Size Mismatch, the provided matrices are not compatible to perform this funtion \n");
        }
        Matrix_return.row = Matrix_1.row;
        Matrix_return.col = Matrix_1.col;

        for (int r = 0; r < Matrix_1.row; r++)
        {
            std::vector<float> col;
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
