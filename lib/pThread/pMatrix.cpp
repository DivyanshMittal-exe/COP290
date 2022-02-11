#include "pMatrix.h"
#include <fstream>
#include <math.h>
#include <pthread.h>

struct mul
{
    // float *upd_loc;
    float upd;
    std::vector<float> r;
    std::vector<float> c;
};

struct add
{
    // std::vector<float> *upd_loc;
    float upd;
    float l1;
    float l2;
};

void *pAdd(void *args)
{
    struct add *a = (struct add *)args;
    float l1 = a->l1;
    float l2 = a->l2;
    // std::vector<float> u = a->upd_loc;
    a->upd = l2 + l1;
    // free(args);
    pthread_exit(NULL);
}

void *pMul(void *args)
{
    struct mul *a = (struct mul *)args;
    std::vector<float> r = a->r;
    std::vector<float> c = a->c;
    float val = 0;
    for (int i = 0; i < r.size(); i++)
    {
        val += r[i] * c[i];
    }
    // *(a->upd_loc) = val;
    a-> upd = val;
    // free(args);
    pthread_exit(NULL);
}

//template <typename float>
pMatrix::pMatrix(const std::string &filename)
{
    std::ifstream input_file(filename);

    if (!input_file.good())
        throw std::runtime_error("File not found. Empty matrix returned");

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

// Constructor for pMatrix class with no argument to initialise as 0 size matrix

//template <typename float>
pMatrix::pMatrix()
{
    row = 0;
    col = 0;
}

//template <typename float>
pMatrix::pMatrix(int r, int c)
{
    row = r;
    col = c;
    std::vector<std::vector<float>> elems(row, std::vector<float>(col, 0));
    elements = elems;
}

//template <typename float>

// Returns element (i,j)
float *pMatrix::getElement(int i, int j) const
{
    std::vector<float> row = elements.at(i);
    return &row.at(j);
}

// Funtion to print a matrix to the given stream

//template <typename float>
void pMatrix::print(const std::string &filename)
{

    std::ofstream output_file(filename);
    output_file << col << std::endl;
    output_file << row << std::endl;

    typename std::vector<std::vector<float>>::iterator r;
    typename std::vector<float>::iterator c;

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            output_file << elements[j][i] << std::endl;
        }
    }
}

//template <typename float>
pMatrix pMatrix::transpose() const
{
    pMatrix Matrix_return(col, row);
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            Matrix_return.elements[c][r] = elements[r][c];
        }
    }
    return Matrix_return;
}
// Funtion to overload the * operation for matrix. Multiply 2 matrices of size axb and bxc to get back a axc size matrix
//  Raises error if size mismatch
//template <typename float>
pMatrix pMatrix::operator*(const pMatrix &Matrix_2)
{
    pMatrix Matrix_return(row, Matrix_2.col);
    std::vector<std::vector<float>> elem;
    try
    {
        if (col != Matrix_2.row)
        {
            throw std::runtime_error("Size Mismatch, the provided matrices are not compatible to perform this funtion \n");
        }
        std::cout << "Less Go";
        pMatrix m2t = Matrix_2.transpose();
        std::cout << "Transposed";
        pthread_t thread[row][Matrix_2.col];
        struct mul ss[row][Matrix_2.col];

        for (int r = 0; r < row; r++)
        {
            for (int c = 0; c < Matrix_2.col; c++)
            {

                // struct mul *a = (mul*)malloc(sizeof(struct mul));
                ss[r][c].r =  (elements.at(r));
                ss[r][c].c =  m2t.elements[c];
                // ss[r][c].upd_loc = Matrix_return.getElement(r, c);
                

                if (pthread_create(&thread[r][c], NULL, pMul, (void*)&ss[r][c]) != 0)
                {
                    perror("Couldn't make threads");
                }
            }
        }
        for (int r = 0; r < row; r++)
        {
            for (int c = 0; c < Matrix_2.col; c++)
            {

                if (pthread_join(thread[r][c], NULL) != 0)
                {
                    perror("Couldn't join threads");
                }
            }
        }
        for (int r = 0; r < row; r++)
        {
            for (int c = 0; c < Matrix_2.col; c++)
            {
                Matrix_return.elements[r][c] = ss[r][c].upd;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return Matrix_return;
}

// Funtion to overload the + operation for matrix. Multiply 2 matrices of size axb and axb to get back a axb size matrix
//  Raises error if size mismatch
//template <typename float>
pMatrix pMatrix::operator+(const pMatrix &Matrix_2)
{
    pMatrix Matrix_return(row, col);
    std::vector<std::vector<float>> elem;
    try
    {
        if (row != Matrix_2.row || col != Matrix_2.col)
        {
            throw std::runtime_error("Size Mismatch, the provided matrices are not compatible to perform this funtion \n");
        }
        pthread_t thread[row][col];
        struct add ss[row][col];

        for (int r = 0; r < row; r++)
        {   
            for (int c = 0; c < col; c++)
            {
            ss[r][c].l1 = elements[r][c];
            ss[r][c].l2 = Matrix_2.elements[r][c];

                if (pthread_create(&thread[r][c], NULL, &pAdd,(void*)&ss[r][c]) != 0)
                {
                    perror("Couldn't make threads");
                }
            }
        }
        for (int r = 0; r < row; r++)
        {

            for (int c = 0; c < col; c++)
            {

                if (pthread_join(thread[r][c], NULL) != 0)
                {
                    perror("Couldn't join threads");
                }
            }
        }
        for (int r = 0; r < row; r++)
        {
            for (int c = 0; c < col; c++)
            {
                Matrix_return.elements[r][c] = ss[r][c].upd;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return Matrix_return;
}