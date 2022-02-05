#include "pMatrix.h"
#include <fstream>
#include <math.h>
#include <pthread.h>


// Constructor for pMatrix class with default file passed

struct activation{
    float* arg1;
    float* arg2;
};

template <typename T>
struct pool{
    float * upd_loc;
    int stride;
    int r;
    int c;
    pMatrix<T> m;
};

struct mul{
    float * upd_loc;
    std::vector<float> r;
    std::vector<float> c;
};

struct add{
    std::vector<float>* upd_loc;
    std::vector<float> r;
    std::vector<float> c;
};

void* pAdd(void* args){
    struct add *a = (struct add *)args;
    std::vector<float> r = a->r;
    std::vector<float> c = a->c;
    std::vector<float>* u = a->upd_loc;
    for (int i = 0; i < r.size(); i++)
    {
        (*u)[i] = r[i]+c[i];
    }
    free(args);
}


void* pMul(void* args){
    struct mul *a = (struct mul *)args;
    std::vector<float> r = a->r;
    std::vector<float> c = a->c;
    float val = 0;
    for (int i = 0; i < r.size(); i++)
    {
        val+= r[i]*c[i];
    }
    *(a->upd_loc) = val;
    free(args);
}

void* pRelu(void* args){
    struct activation *a = (struct activation *)args;
    float val = *(a->arg1);
    *(a->arg2) = val > 0 ? val : 0;
    free(args);
}

void* pTanh(void* args){
    struct activation *a = (struct activation *)args;
    float val = *(a->arg1);
    float ex = exp(val);
    float neg_ex = exp(-val);
    *(a->arg2)  = (ex - neg_ex) / (ex + neg_ex);
    free(args);
}

template <typename T>
void* pMax(void* args){
    struct pool *a = (struct pool *)args;
    int stride = a->stride;
    pMatrix<T> m = a->m;

    float val = m.getElement(a->r , a->c);
    for (int i = 0; i < stride; i++)
    {
        for (int j = 0; j < stride; j++)
        {
            val = std::max(val, m.getElement(a->r + i, a->c + j));
        }
    }
    *(a->upd_loc) = val;
    free(args);
}

template <typename T>
void* pAvg(void* args){
    struct pool *a = (struct pool *)args;
    int stride = a->stride;
    pMatrix<T> m = a->m;

    float val = 0;
    for (int i = 0; i < stride; i++)
    {
        for (int j = 0; j < stride; j++)
        {
            val +=  m.getElement(a->r + i, a->c + j);
        }
    }
    val /= (stride*stride);
    *(a->upd_loc) = val;
    free(args);
}

template <typename T>
void* pMax(void* args){
    struct pool *a = (struct pool *)args;
    int stride = a->stride;
    pMatrix<T> m = a->m;

    float val = m.getElement(a->r , a->c);
    for (int i = 0; i < stride; i++)
    {
        for (int j = 0; j < stride; j++)
        {
            val = std::max(val, getElement(a->r + i, a->c + j));
        }
    }
    *(a->upd_loc) = val;
    free(args);
}


template <typename T>
pMatrix<T>::pMatrix(const std::string &filename)
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

// Constructor for pMatrix class with no argument to initialise as 0 size matrix

template <typename T>
pMatrix<T>::pMatrix()
{
    row = 0;
    col = 0;
    elems(row, std::vector<T>(col, 0));
}


template <typename T>
pMatrix<T>::pMatrix(int r, int c)
{
    row = r;
    col = c;
}

template <typename T>

// Returns element (i,j)
T* pMatrix<T>::getElement(int i, int j) const 
{
    std::vector<T> row = elements.at(i);
    return &row.at(j);
}

//Returns a matrix with relu applied on it

template <typename T>
pMatrix<T> pMatrix<T>::relu()
{
    pMatrix<T> Matrix_return(row,col);

    pthread_t thread[row][col];

    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            struct activation a = malloc(*sizeof(struct activation));
            a.arg1 = getElement(r, c);
            a.arg2 = Matrix_return.getElement(r, c);
        
            if(pthread_create(&thread[r][c],NULL,&pRelu,a)!=0){
                perror("Couldn't make threads");
            }
        }
    }
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {

            if(pthread_join(&thread[r][c],NULL)!=0){
                perror("Couldn't join threads");
            }
        }
    }
    

    return Matrix_return;
}

//Returns a matrix with tanh applied on it

template <typename T>
pMatrix<T> pMatrix<T>::matrix_tanh()
{

    pMatrix<T> Matrix_return(row,col);

    pthread_t thread[row][col];

    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            struct activation a = malloc(*sizeof(struct activation));
            a.arg1 = getElement(r, c);
            a.arg2 = Matrix_return.getElement(r, c);

            if(pthread_create(&thread[r][c],NULL,&pTanh,a)!=0){
                perror("Couldn't make threads");
            }
        }
    }
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {

            if(pthread_join(&thread[r][c],NULL)!=0){
                perror("Couldn't join threads");
            }
        }
    }
    

    return Matrix_return;

}

// Retuns a matrix with max poolong on it

template <typename T>
pMatrix<T> pMatrix<T>::max_pooling(int stride)
{
    if(stride ==0)
        throw std::runtime_error("Incompatible stride error \n");
    
    if(row == col)
        throw std::runtime_error("Column and row size are not the same \n");

    if (col % stride != 0)
        throw std::runtime_error("Stride does not divide matrix dimension \n");
    
    int n_row = row/stride;
    int n_col = col/stride;

    pMatrix<T> Matrix_return(n_row,n_col);
    
    pthread_t thread[n_row][n_col];
    for (int r = 0; r < n_row; ++r)
    {
        for (int c = 0; c < n_row; ++c)
        {
            
            struct pool a = malloc(*sizeof(struct activation));
            a.upd_loc = Matrix_return.getElement(r,c);
            a.stride = stride;
            a.r = r*stride;
            a.c = c*stride;
            a.m = *this;
            if(pthread_create(&thread[r/ stride][c/ stride],NULL,&pMax,a)!=0){
                perror("Couldn't make threads");
            }
        }
    }
    for (int r = 0; r < row; r += stride)
    {
        for (int c = 0; c < col; c += stride)
        {

            if(pthread_join(&thread[r/ stride][c/ stride],NULL)!=0){
                perror("Couldn't join threads");
            }
        }
    }

    return Matrix_return;
}

// Retuns a matrix with avg poolong on it

template <typename T>
pMatrix<T> pMatrix<T>::avg_pooling(int stride)
{

    if(stride ==0)
        throw std::runtime_error("Incompatible stride error \n");
    
    if(row == col)
        throw std::runtime_error("Column and row size are not the same \n");

    if (col % stride != 0)
        throw std::runtime_error("Stride does not divide matrix dimension \n");


    int n_row = row/stride;
    int n_col = col/stride;

    pMatrix<T> Matrix_return(n_row,n_col);
    
    pthread_t thread[n_row][n_col];
    for (int r = 0; r < n_row; ++r)
    {
        for (int c = 0; c < n_row; ++c)
        {
            
            struct pool a = malloc(*sizeof(struct activation));
            a.upd_loc = Matrix_return.getElement(r,c);
            a.stride = stride;
            a.r = r*stride;
            a.c = c*stride;
            a.m = *this;
            if(pthread_create(&thread[r/ stride][c/ stride],NULL,&pAvg,a)!=0){
                perror("Couldn't make threads");
            }
        }
    }
    for (int r = 0; r < row; r += stride)
    {
        for (int c = 0; c < col; c += stride)
        {

            if(pthread_join(&thread[r/ stride][c/ stride],NULL)!=0){
                perror("Couldn't join threads");
            }
        }
    }

    return Matrix_return;
}

//Funtion to print a matrix to the given stream

template <typename T>
void pMatrix<T>::print(const std::string &filename)
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
pMatrix<T> pMatrix<T>::transpose(){
    pMatrix<T> Matrix_return(col,row);
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            Matrix_return.elements[c][r] = elements[r][c]; 
        }
    }
    return Matrix_return;
}
//Funtion to overload the * operation for matrix. Multiply 2 matrices of size axb and bxc to get back a axc size matrix
// Raises error if size mismatch
template <typename T>
pMatrix<T> pMatrix<T>::operator*(const pMatrix<T> &Matrix_2)
{
    pMatrix<T> Matrix_return(row,Matrix_2.col);
    std::vector<std::vector<T>> elem;
    try
    {
        if (col != Matrix_2.row)
        {
            throw std::runtime_error("Size Mismatch, the provided matrices are not compatible to perform this funtion \n");
        }
        pMatrix<T> m2t = Matrix_2.transpose();
        pthread_t thread[row][Matrix_2.col];
            for (int r = 0; r < row; r++)
            {
                for (int c = 0; c < Matrix_2.col; c++)
                {
                
                struct mul a = malloc(*sizeof(struct mul));
                a.r = elements[r];
                a.c = m2t.elements[c];
                a.upd_loc = Matrix_return.getElement(r,c);
                
            
                if(pthread_create(&thread[r][c],NULL,&pMul,a)!=0){
                    perror("Couldn't make threads");
                }
            }
        }
        for (int r = 0; r < row; r++)
        {
            for (int c = 0; c < Matrix_2.col; c++)
            {

                if(pthread_join(&thread[r][c],NULL)!=0){
                    perror("Couldn't join threads");
                }
            }
        }

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
pMatrix<T> pMatrix<T>::operator+(const pMatrix<T> &Matrix_2)
{
    pMatrix<T> Matrix_return(row,col);
    std::vector<std::vector<T>> elem;
    try
    {
        if (row != Matrix_2.row || col != Matrix_2.col)
        {
            throw std::runtime_error("Size Mismatch, the provided matrices are not compatible to perform this funtion \n");
        }
        pthread_t thread[row];
            for (int r = 0; r < row; r++)
            {
                struct mul a = malloc(*sizeof(struct mul));
                a.r = elements[r];
                a.c = Matrix_return.elements[r];
                a.upd_loc = &Matrix_return[r];
                
            
                if(pthread_create(&thread[r][c],NULL,&pMul,a)!=0){
                    perror("Couldn't make threads");
                
            }
        }
        for (int r = 0; r < row; r++)
        {
        
                if(pthread_join(&thread[r][c],NULL)!=0){
                    perror("Couldn't join threads");
                }
            
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return Matrix_return;
}

