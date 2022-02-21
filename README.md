# COP290 Subtask 1


  - [Available Functions](#Available-Functions)
    -   [Fully Connected (FC) Layer](#---fully-connected-fc-layer)
    -   [Non-Linear Activations](#---non-linear-activations)
    -   [Subsampling](#---subsampling)
    -   [Vector of Random Floats To A Vector Of Probabilities](#---vector-of-random-floats-to-a-vector-of-probabilities)
  - [How to input matrix/vector](#how-to-input-matrixvector)
  - [How to run the code](#how-to-run-the-code)
  - [Internal Implementation](#internal-implementation)

## Available Functions
  
  Various functions implemented are:

### -  Fully Connected (FC) Layer

 - Prints a matrix by taking the inner product of an input matrix of dimensions AxB and a weight matrix of dimensions BxC, to output a matrix of dimension AxC. To this output, a bias vector of dimension AXC is then added elementwise.

- 4 implementations available are:
  1. Normal 
    ```
    make
    ./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt
    ```
  1. pThreads 
    ```
    make
    ./yourcode.out pthread fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt
    ```
  1. MKL 
    ```
    make mkl
    ./yourcode.out mkl fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt
    ```
  1. Openblas 
    ```
    make oblas
    ./yourcode.out oblas fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt
    ```


Example: 

```
./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt
```
Filename | Description | Size
------------ | ------------- | -------------
inputmatrix.txt | Contains the input matrix | A x C
weightmatrix.txt | Contains the weight matrix | B x C
biasmatrix.txt | Contains the bias matrix | A x C
outputmatrix.txt | Contains the output matrix obtained by taking inner product of input and weight matrix and adding bias matrix to it | A x C

- **Errors raised**: 
  - Size mismatch for multiplication
  - Size mismatch for addition
    

### -  Non-Linear Activations 
- Prints a matrix with non - linear activations of an input matrix of any size with relu and tanh functions on individual matrix elements

Example:

```
./yourcode.out activation relu inputmatrix.txt outputmatrix.txt
./yourcode.out activation tanh inputmatrix.txt outputmatrix.txt
```

Filename | Description | Size
------------ | ------------- | -------------
inputmatrix.txt | Contains the input matrix | A x B
outputmatrix.txt | Contains the output matrix obtained by applying relu or tanh function on the input matrix | A x B

   

### -  Subsampling

- Prints a matrix with subsampling of square input matrices of any size with max pooling and average pooling functions

Example:

```
./yourcode.out pooling max inputmatrix.txt stride outputmatrix.txt
./yourcode.out pooling average inputmatrix.txt stride outputmatrix.txt
```

Filename | Description | Size
------------ | ------------- | -------------
inputmatrix.txt | Contains the input matrix | A x B
stride | Specify the stride for subsampling | n (Positive Integer)
outputmatrix.txt | Contains the output matrix obtained by subsampling of square input matrices with max pooling or average pooling functions on the input matrix | A x B
    
- **Errors raised**: 
  - Stride size 0
  - Matrix not square
  - Stride does not divide matrix dimension

### -  Vector of Random Floats To A Vector Of Probabilities

- Prints a vector by converting a vector of random floats to a vector of probabilities with softmax and sigmoid functions

Example:

```
./yourcode.out probability softmax inputvector.txt outputvector.txt
./yourcode.out probability sigmoid inputvector.txt outputvector.txt
```

Filename | Description | Size
------------ | ------------- | -------------
inputvector.txt | Contains the input matrix | A x 1
outputvector.txt | Contains vector of probabilities obtained by converting input vector with softmax or sigmoid functions | A x 1
    
<hr>


## How to input matrix/vector

- Store vectors as first line having size of vector and after that single values in each line of the file
- Store matrices as first line having column size, 2nd having row size, and after that values of matrix in column major order in each line of the file

<hr>


## How to run the code

Simply run the make file by `make` command.

Then write the command you want to run, similarly to the example given above. 

The output would be written in the file **outputvector.txt**/**outputmatrix.txt**

## Internal Implementation

To implement the various functions like Fully Connected (FC) Layer ,Non-Linear Activations, Subsampling and Vector of Random Floats To A Vector Of Probabilities, I have created **C++ template classes** with the names Matrix and Vector. The class have functions, to facilitate the implementation, along with operator overloading of + , * operators. Appropriate errors are also raised wherever needed, eg size mismatch, wrong arguments passed, no arguments passed and many more.