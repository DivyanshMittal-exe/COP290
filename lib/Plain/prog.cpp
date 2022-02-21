#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>
#include <chrono>

//./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatr.txt

using namespace std;

//I am storing a matrix as a vector of vectors where each column is stored in a separate vector (Column Major format)

vector<vector<float>> readMatrix(string filename)
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
    float entry;
    vector<vector<float>> mat(A);
    for (int i = 0; i < A; i++)
    {
        for (int j = 0; j < B; j++)
        {
            infile >> entry;
            mat[i].push_back(entry);
        }
    }
    infile.close(); //closing file stream
    return mat;
}

vector<float> readVector(string filename)
{
    int A; // A sized vector

    //Handling file handling exceptions

    ifstream infile;
    infile.open(filename); //opening file stream
    if (!infile)
    {
        throw "Error, File couldn't be opened";
    }
    infile >> A;
    vector<float> vec(A);
    for (int i = 0; i < A; i++)
    {
        infile >> vec[i];
    }
    infile.close(); //closing file stream
    return vec;
}

void writeMatrix(string filename, vector<vector<float>> mat)
{
    //Handling file handling exceptions

    ofstream outfile;
    outfile.open(filename, fstream::out); //opening file stream
    if (!outfile)
    {
        throw "Error, Output file couldn't be opened/created";
    }
    outfile << mat.size() << endl;
    outfile << mat[0].size() << endl;

    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[0].size(); j++)
        {
            outfile << mat[i][j] << endl;
        }
    }
    outfile.close(); //closing file stream
}

void writeVector(string filename, vector<float> vec)
{
    //Handling file handling exceptions

    ofstream outfile;
    outfile.open(filename, fstream::out); //opening file stream
    if (!outfile)
    {
        throw "Error, Output file couldn't be opened/created";
    }
    outfile << vec.size() << endl;

    for (int i = 0; i < vec.size(); i++)
    {
        outfile << vec[i] << endl;
    }
    outfile.close(); //closing file stream
}

vector<vector<float>> add2mat(vector<vector<float>> mat1, vector<vector<float>> mat2)
{
    // Checking that the sizes of the 2 matrices are equal
    if (mat1.size() != mat2.size() || mat1[0].size() != mat2[0].size())
    {
        throw "matrix sizes not same.";
    }
    vector<vector<float>> res(mat1.size());
    for (int i = 0; i < mat1.size(); i++)
    {
        for (int j = 0; j < mat1[0].size(); j++)
        {
            res[i].push_back(mat1[i][j] + mat2[i][j]);
        }
    }
    return res;
}

vector<vector<float>> mul2mat(vector<vector<float>> mat1, vector<vector<float>> mat2)
{
    // Checking that the sizes of the 2 matrices are appropriate
    if (mat1.size() != mat2[0].size())
    {
        throw "matrix sizes not compatible for multiplication.";
    }
    vector<vector<float>> res(mat2.size());
    float temp = 0;
    for (int i = 0; i < mat1[0].size(); i++)
    {
        for (int j = 0; j < mat2.size(); j++)
        {
            temp = 0;
            for (int k = 0; k < mat1.size(); k++)
            {
                temp += mat1[k][i] * mat2[j][k];
                //This might look strange but I have stored the matrix in a column major order so the usual indices are switched
            }
            res[j].push_back(temp);
        }
    }
    return res;
}

void fullyConnected(string input, string weight, string bias, string output)
{
    vector<vector<float>> inputMat = readMatrix(input);
    vector<vector<float>> weightMat = readMatrix(weight);
    vector<vector<float>> biasMat = readMatrix(bias);
    auto start = chrono::steady_clock::now();
    vector<vector<float>> outputMat = add2mat(mul2mat(inputMat, weightMat), biasMat);
    auto end = chrono::steady_clock::now();
    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;
    writeMatrix(output, outputMat);
}

vector<vector<float>> relu(vector<vector<float>> mat)
{
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[0].size(); j++)
        {
            //implementing relu function
            if (mat[i][j] < 0)
            {
                mat[i][j] = 0;
            }
        }
    }
    return mat;
}

vector<vector<float>> tanh(vector<vector<float>> mat)
{
    float x;
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[0].size(); j++)
        {
            //implementing tanh function
            x = mat[i][j];
            mat[i][j] = (exp(2 * x) - 1) / (exp(2 * x) + 1);
        }
    }
    return mat;
}

vector<float> sigmoid(vector<float> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        vec[i] = 1 / (1 + exp(-1 * vec[i]));
    }
    return vec;
}

vector<float> softmax(vector<float> vec)
{
    float sumexp = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        sumexp += exp(vec[i]);
    }
    for (int i = 0; i < vec.size(); i++)
    {
        vec[i] = exp(vec[i]) / sumexp;
    }
    return vec;
}

vector<vector<float>> maxPool(vector<vector<float>> mat, int stride)
{
    //Ensuring stride is valid
    if (stride <= 0 || mat.size() != mat[0].size() || mat.size() % stride != 0)
    {
        throw "stride not valid!";
    }
    float temp;
    vector<vector<float>> res(mat.size() / stride);
    for (int i = 0; i < mat.size() / stride; i++)
    {
        for (int j = 0; j < mat[0].size() / stride; j++)
        {
            temp = mat[i * stride][j * stride]; //initialising temp with the first element of the square
            for (int a = i * stride; a < (i + 1) * stride; a++)
            {
                for (int b = j * stride; b < (j + 1) * stride; b++)
                {
                    temp = max(temp, mat[a][b]);
                }
            }
            res[i].push_back(temp);
        }
    }
    return res;
}

vector<vector<float>> avgPool(vector<vector<float>> mat, int stride)
{
    //Ensuring stride is appropriate
    if (stride <= 0 || mat.size() != mat[0].size() || mat.size() % stride != 0)
    {
        throw "stride not valid!";
    }
    float temp;
    vector<vector<float>> res(mat.size() / stride);
    for (int i = 0; i < mat.size() / stride; i++)
    {
        for (int j = 0; j < mat[0].size() / stride; j++)
        {
            temp = 0;
            for (int a = i * stride; a < (i + 1) * stride; a++)
            {
                for (int b = j * stride; b < (j + 1) * stride; b++)
                {
                    temp += mat[a][b] / (stride * stride);
                }
            }
            res[i].push_back(temp);
        }
    }
    return res;
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
            fullyConnected(argv[2], argv[3], argv[4], argv[5]);
        }
        else if (string(argv[1]) == "activation")
        {
            if (argc != 5)
            {
                throw "Invalid format. Correct format is as follows - ./yourcode.out activation relu|tanh inputmatrix.txt outputmatrix.txt";
            }
            vector<vector<float>> inputMat = readMatrix(argv[3]);
            vector<vector<float>> res;
            if (string(argv[2]) == "relu")
            {
                res = relu(inputMat);
            }
            else if (string(argv[2]) == "tanh")
            {
                res = tanh(inputMat);
            }
            else
            {
                throw "Invalid format. Correct format is as follows - ./yourcode.out activation relu|tanh inputmatrix.txt outputmatrix.txt";
            }
            writeMatrix(argv[4], res);
        }
        else if (string(argv[1]) == "pooling")
        {
            if (argc != 6)
            {
                throw("Invalid format. Correct format is as follows - ./yourcode.out pooling max|average inputmatrix.txt stride outputmatrix.txt");
            }
            vector<vector<float>> inputMat = readMatrix(argv[3]);
            vector<vector<float>> res;

            int stride = atoi(argv[4]);
            if (string(argv[2]) == "max")
            {
                res = maxPool(inputMat, stride);
            }
            else if (string(argv[2]) == "average")
            {
                res = avgPool(inputMat, stride);
            }
            else
            {
                throw("Invalid format. Correct format is as follows - ./yourcode.out pooling max|average inputmatrix.txt stride outputmatrix.txt");
            }
            writeMatrix(argv[5], res);
        }
        else if (string(argv[1]) == "probability")
        {
            if (argc != 5)
            {
                throw("Invalid format. Correct format is as follows - ./yourcode.out probability softmax|sigmoid inputvector.txt outputvector.txt");
            }
            vector<float> inputVec = readVector(argv[3]);
            vector<float> res;
            if (string(argv[2]) == "softmax")
            {
                res = softmax(inputVec);
            }
            else if (string(argv[2]) == "sigmoid")
            {
                res = sigmoid(inputVec);
            }
            else
            {
                throw("Invalid format. Correct format is as follows - ./yourcode.out probability softmax|sigmoid inputvector.txt outputvector.txt");
            }
            writeVector(argv[4], res);
        }
        else
        {
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
