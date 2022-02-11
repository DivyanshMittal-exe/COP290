#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>
#include <mkl.h>
using namespace std;

//I am storing a matrix as a array of doubles (Column Major format)
//For a matrix I am storing the dimension in a pair (col,row)

pair<int, int> readMatrixArr(string filename, double* mat)
{
    int A, B; // AxB matrix

    //Handling file handling exceptions

    ifstream infile;
    infile.open(filename); //opening file stream
    if (!infile)
    {
        throw "Error, File couldn't be opened";
    }
    infile >> A;
    infile >> B;
    mat[0] = A;
    mat[1] = B;
    
    for (int i = 0; i < A*B; i++)
    {
        infile >> mat[i];
    }
    infile.close(); //closing file stream
    pair<int, int> p(A, B);
    // p.first = A;
    // p.second = B;
    return p;
}

void writeMatrix(string filename, double* mat, pair<int,int> dim)
{
    //Handling file handling exceptions

    ofstream outfile;
    outfile.open(filename, fstream::out); //opening file stream
    if (!outfile)
    {
        throw "Error, Output file couldn't be opened/created";
    }
    int A = dim.first;
    int B = dim.second;
    outfile << dim.first << endl;
    outfile << dim.second << endl;

    for (int i = 0; i < A*B; i++)
    {
        outfile << (float)mat[i] << endl;
    }
    outfile.close(); //closing file stream
}

void mklFullyConnected(string input, string weight, string bias, string output){
    double inputMat[2000];
    pair<int,int> inputDim = readMatrixArr(input, inputMat);
    double weightMat[2000];
    pair<int,int> weightDim = readMatrixArr(weight, weightMat);
    double biasMat[2000];
    pair<int,int> biasDim = readMatrixArr(bias, biasMat);


    if (inputDim.first != weightDim.second || inputDim.second != biasDim.second || weightDim.first != biasDim.first)
    {
        throw "matrix sizes not compatible.";
    }

    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, inputDim.second, weightDim.first, inputDim.first, 1.0,  inputMat, inputDim.second, weightMat, weightDim.second, 1.0, biasMat, biasDim.second);
    writeMatrix(output, biasMat, biasDim);
}

int main(int argc, char *argv[])
{
     try
    {
        if (argc == 1)
        {
            // No arguments given
            throw "Invalid format. No arguments given. Check out README for valid format.";
        }
        else if (string(argv[1]) == "fullyconnected")
        {
            if (argc != 6)
            {
                throw "Invalid format. Correct format is as follows - ./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt";
            }
            mklFullyConnected(argv[2], argv[3], argv[4], argv[5]);
        }
    }
    catch (const char *msg)
    {
        //Printing errors in console
        cerr << msg << endl;
    }
    catch (exception e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
