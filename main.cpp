#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "Matrix.h"
#include "Vector.h"

using namespace std;

vector<string> split(string l){
    vector<string> commands;
    istringstream words(l);
    string word;
    while (words >> word)
    {
        commands.push_back(word);
    }
    
    return commands;
}

void show_help(){

}

void mfc(string A,string B,string C){
    Matrix m1(A);
    Matrix m2(B);
    Matrix m3(C);

    Matrix m4 = (m1*m2) + m3;
    m4.print();
}

void mrelu(string A){
    Matrix m1(A);
    Matrix m2 = m1.relu();
    m2.print();
}
void mtanh(string A){
    Matrix m1(A);
    Matrix m2 = m1.matrix_tanh();
    m2.print();
}
void mmaxpool(string A,string Stride){
    Matrix m1(A);
    Matrix m2 = m1.max_pooling(stoi(Stride));
    m2.print();
}
void mavgpool(string A,string Stride){
    Matrix m1(A);
    Matrix m2 = m1.avg_pooling(stoi(Stride));
    m2.print();
}
void vsoftmax(string A){
    Vector m1(A);
    Vector m2 = m1.softmax();
    m2.print();
}
void vsigmoid(string A){
    Vector m1(A);
    Vector m2 = m1.softmax();
    m2.print();
}


int main()
{
    cout << "\033[H\033[J";
    cout << "Welcome!"<<endl;
    cout << "Submission for COP290-2022 Subtask 1 by Divyansh, 2020CS10342" << endl;
    cout << "Enter 'h' for help, 'e' to exit"<<endl;
    
    string command;
    while (true)
    {
        getline(cin,command);
        vector<string> args = split(command);


        if(args.size() == 0)
            continue;



        if( strcmp("fullyconnected" ,args[0].c_str()) == 0){
            if( args.size()!= 4)
                cout << "Invalid number of arguments passed. Please pass 3 files" << endl;
                
            else
                mfc(args[1],args[2],args[3]);
            
        }
        else if(  strcmp("relu" ,args[0].c_str()) == 0){
            if(args.size()!= 2)
                cout << "Invalid number of arguments passed. Please pass 1 file" << endl;
            
            else
                mrelu(args[1]);
        }
        else if(  strcmp("tanh" ,args[0].c_str()) == 0){
            if( args.size()!= 2)
                cout << "Invalid number of arguments passed. Please pass 1 file" << endl;
                
            else
                mtanh(args[1]);
            
            }
        else if(  strcmp("maxpool" ,args[0].c_str()) == 0){
            if( args.size()!= 3)
                cout << "Invalid number of arguments passed. Please pass 1 file and stride" << endl;
            else
                mmaxpool(args[1],args[2]);
            }

        else if(  strcmp("avgpool" ,args[0].c_str()) == 0){
            if( args.size()!= 3)
                cout << "Invalid number of arguments passed. Please pass 1 file and stride" << endl;   
            else
                mavgpool(args[1],args[2]);
            }

        else if(  strcmp("softmax" ,args[0].c_str()) == 0){
            if( args.size()!= 2)
                cout << "Invalid number of arguments passed. Please pass 1 file" << endl;
                 
            else
                vsoftmax(args[1]);
            }

        else if(  strcmp("sigmoid" ,args[0].c_str()) == 0){
            if( args.size()!= 2)
                cout << "Invalid number of arguments passed. Please pass 1 file" << endl;
                 
            else
                vsigmoid(args[1]);
            }

        else if(  strcmp("h" ,args[0].c_str()) == 0){
            show_help();
        }
        else if(  strcmp("e" ,args[0].c_str()) == 0){
            cout << "Thank You!" << endl;
            break;
        }
        else{
            cout << "Invalid commad. Enter h for help, e to exit " <<endl;
        }
        
    }
    

    return 0;
}