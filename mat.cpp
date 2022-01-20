#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

struct mat
{
    int row;
    int col;
    vector<vector<float>> elements;
};

mat readMatrix (string filename){
    ifstream input_file(filename);
    mat ret;
    int r,c;
    input_file >> r;
    input_file >> c;
    ret.row = r;
    ret.col = c;
    vector<vector<float>> elem;
    
    for (int i = 0; i < r; i++)
    {
        vector<float> col;
        for (int j = 0; j < c; j++)
        {
            float val;
            input_file >> val;
            col.push_back(val);
        }
        elem.push_back(col);
    }
    
}

int main(){

    

    return 0;
}