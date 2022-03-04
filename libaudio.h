#include <string>

#if !defined(libaudio_H)
#define libaudio_H

extern void readAudio(std::string filename, float* mat);

extern void relu(int size, float matrix[]);

extern void softmax(int size, float matrix[]);

extern void fullyconnected(int a,int b, int c, float inputMat[],float weightMat[],float biasMat[]);

extern std::pair<int,float> getmax (float arr[],int size);

extern void predict_audio(char* inputfile, char* outputfile);
   
#endif // libaudio_H
