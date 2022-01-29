#include "Vector.h"

Vector::Vector()
{
    size = 0;
}
Vector::Vector(std::string filename)
{
    std::ifstream input_file(filename);
    input_file >> size;
    std::vector<float> elems(size, 0);

    for (int i = 0; i < size; i++)
    {
        float val;
        input_file >> val;
        elems[i] = val;
    }
    elements = elems;
}

Vector Vector::sigmoid()
{
    Vector Vector_return;
    Vector_return.size = size;
    for (auto iter = elements.cbegin(); iter != elements.cend(); ++iter)
    {
        float ele = *iter;
        ele = 1 / (1 + exp(-ele));
        Vector_return.elements.push_back(ele);
    }
    return Vector_return;
}
Vector Vector::softmax()
{
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
        float el = exp(ele) / sum;
        Vector_return.elements.push_back(el);
    }
    return Vector_return;
}

void Vector::print(std::string filename)
{
    std::ofstream output_file(filename);
    output_file << size << std::endl;
    for (int i = 0; i < size; i++)
    {
        output_file << elements[i] << std::endl;
    }
}
