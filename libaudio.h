#include <string>

#if !defined(libaudio_H)
#define libaudio_H

typedef struct{
    int label;
    float prob;
}pred_t;

extern pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred);

extern void readAudio(std::string filename, float* mat);

extern void relu(int size, float matrix[]);

extern void softmax(int size, float matrix[]);

extern void fullyconnected(int a,int b, int c, float inputMat[],float weightMat[],float biasMat[]);

extern pred_t getmax (float arr[],int size);
   
#endif // libaudio_H
