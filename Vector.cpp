#include "Vector.h"



    Vector::Vector(){
        size = 0;
    }
    Vector::Vector(string filename)
    {
        ifstream input_file(filename);
        int i = 0;
        vector<float> elem;
        float read;

        while (input_file >> read)
        {
            elements.push_back(read);
            i+=1;
        }
        size = i;
    }

    Vector Vector::sigmoid(){
        Vector Vector_return;
        Vector_return.size = size;
        for (auto iter = elements.cbegin(); iter != elements.cend(); ++iter)
        {
            float ele = *iter;
            ele = 1 /(1 + exp(-ele));
            Vector_return.elements.push_back(ele);
        }
        return Vector_return;
    }
    Vector Vector::softmax(){
        Vector Vector_return;
        Vector_return.size = size;
        float sum = 0;
        for (auto iter = elements.cbegin(); iter != elements.cend(); ++iter)
        {
            float ele = *iter;
            sum += exp(ele);
        }
        for (auto iter = elements.cbegin(); iter != elements.cend(); ++iter)
        {
            float ele = *iter;
            ele = exp(ele)/sum;
            Vector_return.elements.push_back(ele);
        }
        return Vector_return;
    }

    void Vector:: print(){
    vector<float>::iterator it;
        for (it = elements.begin(); it != elements.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
}
