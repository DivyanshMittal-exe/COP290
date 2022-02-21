#include "pMatrix.h"
#include <fstream>
#include <math.h>
#include <pthread.h>



struct mul
{
    // float *upd_loc;
    std::vector<std::vector<float>> *mult; 
    const std::vector<std::vector<float>>  *m1;
    const std::vector<std::vector<float>>  *m2t;
    int m1i,m1j;
    int m2i,m2j;
    
};



struct add
{
    std::vector<std::vector<float>> *mult; 
    const std::vector<std::vector<float>> *m1;
    const std::vector<std::vector<float>> *m2;
    int i,j;
};



void *pAdd(void *args)
{
    struct add *a = (struct add *)args;
    std::vector<std::vector<float>> &mult  = *(a-> mult); 
    const std::vector<std::vector<float>>  &m1 = *(a-> m1);
    const std::vector<std::vector<float>>  &m2 = *(a-> m2);
    int i = a-> i;
    int j = a-> j;


    for (int row_i = i; row_i < j;row_i++) {
        
            auto row1 = m1.cbegin() + row_i;
            auto row2 = m2.cbegin() + row_i;
            for (int k = 0; k < row1->size(); k++)
            {
                auto col1 = row1->cbegin() + k;
                auto col2 = row2->cbegin() + k;
                mult[row_i][k] = (*col1)+ (*col2);
            }
    }
    

    pthread_exit(NULL);
}



void *pMul(void *args)
{
    struct mul *a = (struct mul *)args;
    std::vector<std::vector<float>> &mult  = *(a-> mult); 
    const std::vector<std::vector<float>>  &m1 = *(a-> m1);
    const std::vector<std::vector<float>>  &m2t = *(a-> m2t);
    int m1i = a-> m1i;
    int m1j = a-> m1j;
    int m2i = a-> m2i;
    int m2j = a-> m2j;


    for (int i = m1i; i < m1j;i++) {
        for (int j = m2i; j < m2j;j++) {
            auto row1 = m1.cbegin() + i;
            auto row2 = m2t.cbegin() + j;
            float sum = 0;
            for (int k = 0; k < row1->size(); k++)
            {
                auto col1 = row1->cbegin() + k;
                auto col2 = row2->cbegin() + k;
                sum += (*col1)*(*col2);
            }
            mult[i][j] = sum;
        }
    }

    pthread_exit(NULL);
}



pMatrix pMatrix::transpose() const
{
    
    pMatrix Matrix_return(Matrix<float>::col, Matrix<float>::row);
    for (int r = 0; r < Matrix<float>::row; r++)
    {
        for (int c = 0; c < Matrix<float>::col; c++)
        {
            Matrix_return.elements[c][r] = Matrix<float>::elements[r][c];
        }
    }
    return Matrix_return;
}


// Funtion to overload the * operation for matrix. Multiply 2 matrices of size axb and bxc to get back a axc size matrix
//  Raises error if size mismatch


pMatrix pMatrix::operator*(const pMatrix &Matrix_2)
{   
    
    pMatrix Matrix_return(Matrix<float>::row, Matrix_2.col);
    std::vector<std::vector<float>> elem;
    try
    {
        if (Matrix<float>::col != Matrix_2.row)
        {
            throw std::runtime_error("Size Mismatch, the provided matrices are not compatible to perform this funtion \n");
        }
        pMatrix m2t = Matrix_2.transpose();
        pthread_t thread[4];
        struct mul ss[4];

        std::vector<std::vector<float>> res(Matrix<float>::row, std::vector<float>(Matrix_2.col, 0));

            
        for (int i = 0; i < 4; i++)
        {
            ss[i].mult = &res;
            ss[i].m1 = &(Matrix<float>::elements);
            ss[i].m2t = &m2t.elements;
            
        }

        ss[0].m1i = 0;
        ss[0].m1j = Matrix<float>::row/2;
        ss[0].m2i = 0;
        ss[0].m2j = m2t.Matrix<float>::row/2;

        ss[1].m1i = 0;
        ss[1].m1j = Matrix<float>::row/2;
        ss[1].m2i = m2t.Matrix<float>::row/2;
        ss[1].m2j = m2t.Matrix<float>::row;

        ss[2].m1i = Matrix<float>::row/2;
        ss[2].m1j = Matrix<float>::row;
        ss[2].m2i = 0;
        ss[2].m2j = m2t.Matrix<float>::row/2;

        ss[3].m1i = Matrix<float>::row/2;
        ss[3].m1j = Matrix<float>::row;
        ss[3].m2i = m2t.Matrix<float>::row/2;
        ss[3].m2j = m2t.Matrix<float>::row;


        for (int i = 0; i < 4; i++)
        {
            if (pthread_create(&thread[i], NULL, pMul, (void*)&ss[i]) != 0)
            {
                perror("Couldn't make threads");
            }
        }

        for (int i = 0; i < 4; i++)
        {
            if (pthread_join(thread[i], NULL) != 0)
                {
                    perror("Couldn't join threads");
                }
        }
        
        Matrix_return.elements = res;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return Matrix_return;
}

// Funtion to overload the + operation for matrix. Multiply 2 matrices of size axb and axb to get back a axb size matrix
//  Raises error if size mismatch


pMatrix pMatrix::operator+(const pMatrix &Matrix_2)
{
    
    
    pMatrix Matrix_return(Matrix<float>::row, Matrix<float>::col);
    std::vector<std::vector<float>> elem;
    try
    {
        if (Matrix<float>::row != Matrix_2.row || Matrix<float>::col != Matrix_2.col)
        {
            throw std::runtime_error("Size Mismatch, the provided matrices are not compatible to perform this funtion \n");
        }
        pthread_t thread[4];
        struct add ss[4];

        std::vector<std::vector<float>> res(Matrix<float>::row, std::vector<float>(Matrix<float>::col, 0));

            
        for (int i = 0; i < 4; i++)
        {
            ss[i].mult = &res;
            ss[i].m1 = &(Matrix<float>::elements);
            ss[i].m2 = &Matrix_2.elements;
        }

        ss[0].i = 0;
        ss[0].j = Matrix<float>::row/4;

        ss[1].i = Matrix<float>::row/4;
        ss[1].j = Matrix<float>::row/2;
       
        ss[2].i = Matrix<float>::row/2;
        ss[2].j = 3*Matrix<float>::row/4;

        ss[3].i = 3*Matrix<float>::row/4;
        ss[3].j = Matrix<float>::row;
       


        for (int i = 0; i < 4; i++)
        {
            if (pthread_create(&thread[i], NULL, pAdd, (void*)&ss[i]) != 0)
            {
                perror("Couldn't make threads");
            }
        }

        for (int i = 0; i < 4; i++)
        {
            if (pthread_join(thread[i], NULL) != 0)
                {
                    perror("Couldn't join threads");
                }
        }
        
        Matrix_return.elements = res;
    
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return Matrix_return;
}