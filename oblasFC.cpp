#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>
#include <cblas.h>
#include <chrono>



//I am storing a matrix as a array of doubles (Column Major format)
//For a matrix I am storing the dimension in a pair (col,row)

std::pair<int, int> readMatrixArr(std::string filename, float* mat)
{
    int A, B; // AxB matrix

    //Handling file handling exceptions

    std::ifstream infile;
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
    std::pair<int, int> p(A, B);
    // p.first = A;
    // p.second = B;
    return p;
}

void writeMatrix(std::string filename, float* mat, std::pair<int,int> dim)
{
    //Handling file handling exceptions

    std::ofstream outfile;
    outfile.open(filename, std::fstream::out); //opening file stream
    if (!outfile)
    {
        throw "Error, Output file couldn't be opened/created";
    }
    int A = dim.first;
    int B = dim.second;
    outfile << dim.first << std::endl;
    outfile << dim.second << std::endl;

    for (int i = 0; i < A*B; i++)
    {
        outfile << (float)mat[i] << std::endl;
    }
    outfile.close(); //closing file stream
}

int oBFullyConnected(std::string input, std::string weight, std::string bias, std::string output){

    float inputMat[100000];
    std::pair<int,int> inputDim = readMatrixArr(input, inputMat);
    float weightMat[100000];
    std::pair<int,int> weightDim = readMatrixArr(weight, weightMat);
    float biasMat[100000];
    std::pair<int,int> biasDim = readMatrixArr(bias, biasMat);


    if (inputDim.first != weightDim.second || inputDim.second != biasDim.second || weightDim.first != biasDim.first)
    {
        throw "matrix sizes not compatible.";
    }
    auto start = std::chrono::steady_clock::now();
    cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, inputDim.second, weightDim.first, inputDim.first, 1.0,  inputMat, inputDim.second, weightMat, weightDim.second, 1.0, biasMat, biasDim.second);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time in microseconds: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << " µs" << std::endl;

    writeMatrix(output, biasMat, biasDim);

    return (int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
}

void timer()
{
    std::string base = "testcases/100/";
    std::string input = base + "inputmatrix.txt";
    std::string weight = base + "weightmatrix.txt";
    std::string bias = base + "biasmatrix.txt";
    std::string output = base + "outputOBlas.txt";

    std::ofstream outfile;


    std::string filename = "data/oblas100.dat";
    outfile.open(filename, std::fstream::out); //opening file stream
    if (!outfile)
    {
        throw "Error, Data file couldn't be opened/created";
    }
    
    for(int i = 0; i < 20; i++){
        int elapsed_time  = oBFullyConnected(input, weight, bias, output);
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
        else if (std::string(argv[1]) == "oblas" && std::string(argv[2]) == "fullyconnected")
        {
            if (argc != 7)
            {
                throw "Invalid format. Correct format is as follows - ./yourcode.out oblas fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt";
            }
            oBFullyConnected(argv[3], argv[4], argv[5], argv[6]);
        }else if (std::string(argv[1]) == "timer" && argc == 2) {
            timer();
        }else {
            //Invalid arguments
            throw "Invalid Input. Check out README for valid parameter format.";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
