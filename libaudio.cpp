#include "libaudio.h"
#include <vector>
#include <mkl.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "dnn_weights.h"



void readAudio(const char* filename, float* mat)
{
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

void relu(const int size, float matrix[]){
    for (int i = 0; i < size; i++)
        {
            matrix[i] = matrix[i]  > 0 ? matrix[i]  : 0;
        }
}
void softmax(const int size, float matrix[]){
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

void fullyconnected(const int a,const int b, const int c, float inputMat[],float weightMat[],float biasMat[]){

    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, a, c, b, 1.0,  inputMat, b, weightMat, c, 1.0, biasMat,c);

}

pred_t getmax (const int size,float arr[]){
    float max_val= 0.0f;
    int max_locn = 0;
    for (int i = 0; i < size; i++)
    {   
        max_val = std::max(max_val,arr[i]);
        max_locn = max_val==arr[i] ? i:max_locn;
    }
    arr[max_locn] *= -1;
    pred_t to_return;
    to_return.label = max_locn;
    to_return.prob = max_val;
    return to_return;
}

pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred){
    float w1[] = IP1_WT;
    float w2[] = IP2_WT;
    float w3[] = IP3_WT;
    float w4[] = IP4_WT;

    float b1[] = IP1_BIAS;
    float b2[] = IP2_BIAS;
    float b3[] = IP3_BIAS;
    float b4[] = IP4_BIAS;

    float inputMat[250];
    readAudio(audiofeatures, inputMat);

    fullyconnected(1,250,144,inputMat,w1,b1);
    relu(144,b1);
    fullyconnected(1,144,144,b1,w2,b2);
    relu(144,b2);
    fullyconnected(1,144,144,b2,w3,b3);
    relu(144,b3);
    fullyconnected(1,144,12,b3,w4,b4);
    softmax(12,b4);
    
    pred[0] = getmax(12,b4);
    pred[1] = getmax(12,b4);
    pred[2] = getmax(12,b4);
    return pred;

}
