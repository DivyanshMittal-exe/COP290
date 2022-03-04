#include "libaudio.h"
#include <vector>
#include <mkl.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "dnn_weights.h"



void readAudio(char* filename, float* mat)
{
    int A, B; // AxB matrix

    //Handling file handling exceptions
    std::ifstream infile;
    infile.open(filename); //opening file stream
    if (!infile)
    {
        throw "Error, File couldn't be opened";
    }
    
    for (int i = 0; i < 250; i++)
    {
        infile >> mat[i];
    }

    infile.close(); //closing file stream
}

void relu(int size, float matrix[]){
    for (int i = 0; i < size; i++)
        {
            matrix[i] = matrix[i]  > 0 ? matrix[i]  : 0;
        }
}
void softmax(int size, float matrix[]){
    float sum = 0.0f;
    for (int i=0;i < size;i++)
    {
        sum += exp(matrix[i]);
    }
    for (int i=0;i < size;i++)
    {
        matrix[i] = exp(matrix[i])/sum;
    }
}

void fullyconnected(int a,int b, int c, float inputMat[],float weightMat[],float biasMat[]){

    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, a, c, b, 1.0,  inputMat, b, weightMat, c, 1.0, biasMat,c);

}

std::pair<int,float> getmax (float arr[],int size = 12){
    float max_val= 0.0f;
    int max_locn = 0;
    for (int i = 0; i < size; i++)
    {   
        max_val = std::max(max_val,arr[i]);
        max_locn = max_val==arr[i] ? i:max_locn;
    }
    arr[max_locn] *= -1;
    std::pair<int, float> p(max_locn, max_val);
    return p;
}

void predict_audio(char* inputfile, char* outputfile){
    float w1[] = IP1_WT;
    float w2[] = IP2_WT;
    float w3[] = IP3_WT;
    float w4[] = IP4_WT;

    float b1[] = IP1_BIAS;
    float b2[] = IP2_BIAS;
    float b3[] = IP3_BIAS;
    float b4[] = IP4_BIAS;

    float inputMat[250];
    readAudio(inputfile, inputMat);

    fullyconnected(1,250,144,inputMat,w1,b1);
    relu(144,b1);
    fullyconnected(1,144,144,b1,w2,b2);
    relu(144,b2);
    fullyconnected(1,144,144,b2,w3,b3);
    relu(144,b3);
    fullyconnected(1,144,12,b3,w4,b4);
    softmax(12,b4);

    for(int i = 0; i< 12 ;i++){
        std::cout << b4[i] << " ";
    }

    std::string audios[] = {"silence","unknown","yes","no","up","down","left","right","on","off","stop","go"};
    std::pair<int,float> pred1 = getmax(b4);
    std::pair<int,float> pred2 = getmax(b4);
    std::pair<int,float> pred3 = getmax(b4);

    std::ofstream outfile;
    outfile.open(outputfile , std::ios_base::app | std::ios_base::out);
    outfile << inputfile << " ";
    outfile << audios[pred1.first] << " " << audios[pred2.first] << " " << audios[pred3.first] << " " ;
    outfile << pred1.second << " "<< pred2.second << " " << pred3.second << " ";
    outfile << std::endl;
    outfile.close();

}
