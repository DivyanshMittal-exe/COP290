#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "Matrix.h"
#include "Vector.h"

using namespace std;


void show_help(){
    cout << "Available commands are:" <<endl;
    
    cout << "->fullyconnected inputmatrix_textfile weightmatrix_textfile biasmatrix_textfile" <<endl;
    cout << "       Prints a matrix by taking the inner product of an input matrix of dimensions AxB and a weight matrix of dimensions BxC, to output a matrix of dimension AxC. To this output, a bias vector of dimension AXC is then added elementwise." <<endl;
    cout << "       Eg: fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt"<< endl;
    cout << endl;

    cout << "->relu inputmatrix_textfile " <<endl;
    cout << "->tanh inputmatrix_textfile " <<endl;
    cout << "       Prints a matrix with non-linear activations of an input matrix of any size with relu and tanh functions on individual matrix elements" <<endl;
    cout << "       Eg: relu inputmatrix.txt "<< endl;
    cout << "       Eg: tanh inputmatrix.txt "<< endl;
    cout << endl;
    

    cout << "->maxpool inputmatrix_textfile stride" <<endl;
    cout << "->avgpool inputmatrix_textfile stride" <<endl;
    cout << "       Prints a matrix with subsampling of square input matrices of any size with max pooling and average pooling functions" <<endl;
    cout << "       Eg: maxpool inputmatrix.txt 5"<< endl;
    cout << "       Eg: avgpool inputmatrix.txt 5"<< endl;
    cout << endl;


    cout << "->sigmoid inputmatrix_textfile" <<endl;
    cout << "->softmax inputmatrix_textfile" <<endl;
    cout << "       Prints a vector by converting a vector of random floats to a vector of probabilities with softmax and sigmoid functions" <<endl;
    cout << "       Eg: sigmoid inputmatrix.txt"<< endl;
    cout << "       Eg: softmax inputmatrix.txt"<< endl;
    cout << endl;


}

void mfc(string A,string B,string C,string D){
    Matrix m1(A);
    Matrix m2(B);
    Matrix m3(C);

    Matrix m4 = (m1*m2) + m3;
    m4.print(D);
}

void mrelu(string A,string B){
    Matrix m1(A);
    Matrix m2 = m1.relu();
    m2.print(B);
}
void mtanh(string A,string B){
    Matrix m1(A);
    Matrix m2 = m1.matrix_tanh();
    m2.print(B);
}
void mmaxpool(string A,string Stride,string B){
    Matrix m1(A);
    Matrix m2 = m1.max_pooling(stoi(Stride));
    m2.print(B);
}
void mavgpool(string A,string Stride,string B){
    Matrix m1(A);
    Matrix m2 = m1.avg_pooling(stoi(Stride));
    m2.print(B);
}
void vsoftmax(string A,string B){
    Vector m1(A);
    Vector m2 = m1.softmax();
    m2.print(B);
}
void vsigmoid(string A,string B){
    Vector m1(A);
    Vector m2 = m1.softmax();
    m2.print(B);
}


int main(int argc, char* argv[])
{
    // cout << "\033[H\033[J";
    // cout << "Welcome!"<<endl;
    // cout << "Submission for COP290-2022 Subtask 1 by Divyansh, 2020CS10342" << endl;
    // cout << "Enter 'h' for help, 'e' to exit"<<endl;



        if(argc == 1)
            throw runtime_error("Function not given.\n");



        if( strcmp("fullyconnected" ,argv[1]) == 0){
            if( argc!= 6)
                throw runtime_error("Invalid number of arguments passed.\n");
                
            else
                mfc(argv[2],argv[3],argv[4],argv[5]);
            
        }
        else if( strcmp("activation" ,argv[1]) == 0){
            if( argc!= 5)
                throw runtime_error("Invalid number of arguments passed.\n");

            if( strcmp("relu" ,argv[2]) == 0){
                mrelu(argv[3],argv[4]);
            }else if( strcmp("tanh" ,argv[2]) == 0){
                mtanh(argv[3],argv[4]);

            }else {
                //Implement error
                throw runtime_error("Enter relu or tanh.\n");
            }
        }
        else if( strcmp("pooling" ,argv[1]) == 0){
            if( argc!= 6)
                throw runtime_error("Invalid number of arguments passed.\n");


            if( strcmp("max" ,argv[2]) == 0){
                mmaxpool(argv[3],argv[4],argv[5]);
            }else if( strcmp("average" ,argv[2]) == 0){
                mavgpool(argv[3],argv[4],argv[5]);

            }else {
                //Implement error
                throw runtime_error("Enter max or average.\n");

            }
        }
        else if( strcmp("probability" ,argv[1]) == 0){
            if( argc!= 5)
                throw runtime_error("Invalid number of arguments passed.\n");

            if( strcmp("softmax" ,argv[2]) == 0){
                vsoftmax(argv[3],argv[4]);
            }else if( strcmp("sigmoid" ,argv[2]) == 0){
                vsigmoid(argv[3],argv[4]);

            }else {
                //Implement error
                throw runtime_error("Enter softmax or sigmoid.\n");
            }
        }
        else{
            throw runtime_error("Invalid command passed.\n");
        }
    

    return 0;
}