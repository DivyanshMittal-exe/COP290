#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

struct sizeMismatch : public std::exception
{
	const char * what () const throw ()
    {
    	return "Matrix size mismatch";
    }
};


struct mat
{
    int row;
    int col;
    vector<vector<float>> elements;
};

float getElement(mat m, int i, int j){
    
    vector<float> row = m.elements.at(i);
    return row.at(j);
}

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
    ret.elements = elem;
    return ret;
}

mat multiply(mat m1,mat m2){
    mat ret;
    vector<vector<float>> elem;
    try
    {
        if(m1.col!=m2.row){
            throw sizeMismatch();
        }
        ret.row = m1.row;
        ret.col = m2.col;

        for (int r = 0; r < m1.row; r++)
        {
            vector<float> col;
            for (int c = 0; c < m2.col; c++)
            {
                float val = 0.0f;
                for (int i = 0; i < m1.col; i++)
                {
                    val += getElement(m1,r,i)*getElement(m2,i,c);
                }
                col.push_back(val);
            }
            elem.push_back(col);
        }
        ret.elements = elem;
    }
    catch(sizeMismatch& e){
        std::cerr << e.what() << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return ret;
}


mat add(mat m1,mat m2){
    mat ret;
    vector<vector<float>> elem;
    try
    {
        if(m1.row!=m2.row || m1.col!=m2.col){
            throw sizeMismatch();
        }
        ret.row = m1.row;
        ret.col = m1.col;

        for (int r = 0; r < m1.row; r++)
        {
            vector<float> col;
            for (int c = 0; c < m1.col; c++)
            {
                float val =  getElement(m1,r,c) + getElement(m2,r,c);
                col.push_back(val);
            }
            elem.push_back(col);
        }
        ret.elements = elem;
    }
    catch(sizeMismatch& e){
        std::cerr << e.what() << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return ret;
}

mat add(mat m1,mat m2){
    mat ret;
    vector<vector<float>> elem;
    try
    {
        if(m1.row!=m2.row || m1.col!=m2.col){
            throw sizeMismatch();
        }
        ret.row = m1.row;
        ret.col = m1.col;

        for (int r = 0; r < m1.row; r++)
        {
            vector<float> col;
            for (int c = 0; c < m1.col; c++)
            {
                float val =  getElement(m1,r,c) + getElement(m2,r,c);
                col.push_back(val);
            }
            elem.push_back(col);
        }
        ret.elements = elem;
    }
    catch(sizeMismatch& e){
        std::cerr << e.what() << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return ret;
}


mat relu(mat m1){
    mat ret;
    vector<vector<float>> elem;
    ret.row = m1.row;
    ret.col = m1.col;

    for (int r = 0; r < m1.row; r++)
    {
        vector<float> col;
        for (int c = 0; c < m1.col; c++)
        {
            float val =  getElement(m1,r,c);
            val = val > 0 ? val:0;
            col.push_back(val);
        }
        elem.push_back(col);
    }
    ret.elements = elem;

    return ret;
}

mat mat_tanh(mat m1){
    mat ret;
    vector<vector<float>> elem;
    ret.row = m1.row;
    ret.col = m1.col;

    for (int r = 0; r < m1.row; r++)
    {
        vector<float> col;
        for (int c = 0; c < m1.col; c++)
        {
            float val =  tanh(getElement(m1,r,c));
            col.push_back(val);
        }
        elem.push_back(col);
    }
    ret.elements = elem;

    return ret;
}

mat max_pooling(mat m1,int stride){
    mat ret;
    vector<vector<float>> elem;
    ret.row = m1.row/stride;
    ret.col = m1.col/stride;

    for (int r = 0; r < m1.row; r+=stride)
    {
        vector<float> col;
        for (int c = 0; c < m1.col; c+=stride)
        {
            float val = getElement(m1,r,c);
            for (int i = 0; i < stride; i++)
            {
                for (int j = 0; j < stride; j++)
                {
                    val = max(val,getElement(m1,r+i,c+j));
                }
            }
            col.push_back(val);
        }
        elem.push_back(col);
    }
    ret.elements = elem;

    return ret;
}

mat avg_pooling(mat m1,int stride){
    mat ret;
    vector<vector<float>> elem;
    ret.row = m1.row/stride;
    ret.col = m1.col/stride;

    for (int r = 0; r < m1.row; r+=stride)
    {
        vector<float> col;
        for (int c = 0; c < m1.col; c+=stride)
        {
            float val = 0.0f;
            for (int i = 0; i < stride; i++)
            {
                for (int j = 0; j < stride; j++)
                {
                    val += getElement(m1,r+i,c+j);
                }
            }
            val /= (stride*stride);
            col.push_back(val);
        }
        elem.push_back(col);
    }
    ret.elements = elem;

    return ret;
}

int main(){

    

    return 0;
}