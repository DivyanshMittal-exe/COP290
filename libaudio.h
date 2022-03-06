#include <string>

#if !defined(libaudio_H)
#define libaudio_H

typedef struct{
    int label;
    float prob;
}pred_t;

extern pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred);

extern void readAudio(const char* filename, float* mat);

extern void relu(const int size, float matrix[]);

extern void softmax(const int size, float matrix[]);

extern void fullyconnected(const int a,const int b, const int c, float inputMat[],float weightMat[],float biasMat[]);

extern pred_t getmax (const int size,float arr[]);
   
#endif // libaudio_H
