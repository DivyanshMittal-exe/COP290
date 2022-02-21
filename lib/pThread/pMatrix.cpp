#include "pMatrix.h"
#include <fstream>
#include <math.h>
#include <pthread.h>


// The final matrix is divided into 16 parts and elemnts of each part are computed via a single thread. 
// Since they are exclusive, no clash happens
// Pointer is passed and constant and refernece is used to prevent overhead from copying matrices
struct fc
{
    std::vector<std::vector<float>> *mult; 
    const std::vector<std::vector<float>>  *m1;
    const std::vector<std::vector<float>>  *m2t;
    const std::vector<std::vector<float>>  *m3;
    int m1i,m1j;
    int m2i,m2j;
    
};


void *pFC(void *args)
{
    struct fc *a = (struct fc *)args;
    std::vector<std::vector<float>> &mult  = *(a-> mult); 
    const std::vector<std::vector<float>>  &m1 = *(a-> m1);
    const std::vector<std::vector<float>>  &m2t = *(a-> m2t);
    const std::vector<std::vector<float>>  &m3 = *(a-> m3);
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
            auto row3 = m3.cbegin() + i;
            auto col3 = row3->cbegin() + j;

            mult[i][j] = sum + *col3;
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
pMatrix fc(const pMatrix &m1,const pMatrix &m2,const pMatrix &m3){
    pMatrix Matrix_return(m1.row, m2.col);
    try
    {
        if (m1.col != m2.row)
        {
            throw std::runtime_error("Size Mismatch, the provided matrices are not compatible to perform this funtion \n");
        }
        if (m1.row != m3.row || m2.col != m3.col)
        {
            throw std::runtime_error("Size Mismatch, the provided matrices are not compatible to perform this funtion \n");
        }

        pMatrix m2t = m2.transpose();
        const int thread_c = 4;

        pthread_t thread[thread_c][thread_c];
        struct fc ss[thread_c][thread_c];

        std::vector<std::vector<float>> res(m3.row, std::vector<float>(m3.col, 0));


        for (int i = 0; i < thread_c; i++)
        {
            for (int j = 0; j < thread_c; j++)
            {
                ss[i][j].mult = &res;
                ss[i][j].m1 = &m1.elements;
                ss[i][j].m2t = &m2t.elements;
                ss[i][j].m3= &m3.elements;

                ss[i][j].m1i = i*(m1.row/thread_c);
                ss[i][j].m1j = ((i+1)*m1.row)/thread_c;
                ss[i][j].m2i = j*(m2t.row/thread_c);
                ss[i][j].m2j = ((j+1)*m2t.row)/thread_c;
            }
            
        }
        


        for (int i = 0; i < thread_c; i++)
        {
            for (int j = 0; j < thread_c; j++)
            {
                if (pthread_create(&thread[i][j], NULL, pFC, (void*)&ss[i][j]) != 0)
                {
                    perror("Couldn't make threads");
                }
            }
        }

        for (int i = 0; i < thread_c; i++)
        {
            for (int j = 0; j < thread_c; j++)
            {
                if (pthread_join(thread[i][j], NULL) != 0)
                {
                    perror("Couldn't join threads");
                }
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