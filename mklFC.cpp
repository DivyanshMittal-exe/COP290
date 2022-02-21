#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>
#include <mkl.h>
#include <chrono>

using namespace std;

//I am storing a matrix as a array of doubles (Column Major format)
//For a matrix I am storing the dimension in a pair (col,row)

pair<int, int> readMatrixArr(string filename, float* mat)
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

void writeMatrix(string filename, float* mat, pair<int,int> dim)
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

int mklFullyConnected(string input, string weight, string bias, string output){

    float inputMat[100000];
    pair<int,int> inputDim = readMatrixArr(input, inputMat);
    float weightMat[100000];
    pair<int,int> weightDim = readMatrixArr(weight, weightMat);
    float biasMat[100000];
    pair<int,int> biasDim = readMatrixArr(bias, biasMat);


    if (inputDim.first != weightDim.second || inputDim.second != biasDim.second || weightDim.first != biasDim.first)
    {
        throw "matrix sizes not compatible.";
    }
    auto start = chrono::steady_clock::now();
    cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, inputDim.second, weightDim.first, inputDim.first, 1.0,  inputMat, inputDim.second, weightMat, weightDim.second, 1.0, biasMat, biasDim.second);
    auto end = chrono::steady_clock::now();
    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;

    writeMatrix(output, biasMat, biasDim);

    return (int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
}

void timer()
{
    std::string base = "testcases/100/";
    std::string input = base + "inputmatrix.txt";
    std::string weight = base + "weightmatrix.txt";
    std::string bias = base + "biasmatrix.txt";
    std::string output = base + "outputMkl.txt";

    std::ofstream outfile;


    std::string filename = "data/mkl100.dat";
    outfile.open(filename, std::fstream::out); //opening file stream
    if (!outfile)
    {
        throw "Error, Data file couldn't be opened/created";
    }
    
    for(int i = 0; i < 20; i++){
        int elapsed_time  = mklFullyConnected(input, weight, bias, output);
        outfile << elapsed_time << std::endl;
    }
    outfile.close();
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
        eelse if (string(argv[1]) == "mkl" && string(argv[2]) == "fullyconnected")
        {
            if (argc != 6 || argc != 7)
            {
                throw "Invalid format. Correct format is as follows - ./yourcode.out mkl fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt";
            }
            mklFullyConnected(argv[2], argv[3], argv[4], argv[5]);
        }else if (string(argv[1]) == "timer" && argc == 2) {
            timer();
        }else {
            //Invalid arguments
            throw "Invalid Input. Check out README for valid parameter format.";
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
