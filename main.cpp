#include <iostream>
#include <string.h>
#include "Matrix.h"
#include "Vector.h"


void mfc(std::string input_file, std::string weight_matrix, std::string bias_matrix, std::string output_file)
{
    try
    {
        Matrix<float> m_in(input_file);
        Matrix<float> m_wgt(weight_matrix);
        Matrix<float> m_bias(bias_matrix);

        Matrix<float> m_out = (m_in * m_wgt) + m_bias;
        m_out.print(output_file);
    }
    catch (const std::exception &e)
    {
        throw;
    }
}

void mrelu(std::string input_file, std::string output_file)
{
    try
    {
        Matrix<float> m_in(input_file);
        Matrix<float> m_out = m_in.relu();
        m_out.print(output_file);
    }
    catch (const std::exception &e)
    {
        throw;
    }
}
void mtanh(std::string input_file, std::string output_file)
{
    try
    {
        Matrix<float> m_in(input_file);
        Matrix<float> m_out = m_in.matrix_tanh();
        m_out.print(output_file);
    }
    catch (const std::exception &e)
    {
        throw;
    }
}
void mmaxpool(std::string input_file, std::string Stride, std::string output_file)
{
    try
    {
        Matrix<float> m_in(input_file);
        Matrix<float> m_out = m_in.max_pooling(stoi(Stride));
        m_out.print(output_file);
    }
    catch (const std::exception &e)
    {
        throw;
    }
}
void mavgpool(std::string input_file, std::string Stride, std::string output_file)
{

    try
    {
        Matrix<float> m_in(input_file);
        Matrix<float> m_out = m_in.avg_pooling(stoi(Stride));
        m_out.print(output_file);
    }
    catch (const std::exception &e)
    {
        throw;
    }
}
void vsoftmax(std::string input_file, std::string output_file)
{

    try
    {
        Vector<float> m_in(input_file);
        Vector<float> m_out = m_in.softmax();
        m_out.print(output_file);
    }
    catch (const std::exception &e)
    {
        throw;
    }
}
void vsigmoid(std::string input_file, std::string output_file)
{

    try
    {
        Vector<float> m_in(input_file);
        Vector<float> m_out = m_in.sigmoid();
        m_out.print(output_file);
    }
    catch (const std::exception &e)
    {
        throw;
    }
}

int main(int argc, char *argv[])
{
    // cout << "\033[H\033[J";
    // cout << "Welcome!"<<endl;
    // cout << "Submission for COP290-2022 Subtask 1 by Divyansh, 2020CS10342" << endl;
    // cout << "Enter 'h' for help, 'e' to exit"<<endl;

    try
    {
        /* code */

        if (argc <= 1)
            throw std::runtime_error("Function not given. Please pass a function and input output parameters\n");

        if(argc == 2)
            throw std::runtime_error("Pass input output parameters too and not just name of the function.\n");

        if (strcmp("fullyconnected", argv[1]) == 0)
        {
            if (argc != 6)
                throw std::runtime_error("Invalid number of arguments passed.\n");

            else
                mfc(argv[2], argv[3], argv[4], argv[5]);
        }
        else if (strcmp("activation", argv[1]) == 0)
        {
            if (argc != 5)
                throw std::runtime_error("Invalid number of arguments passed.\n");

            if (strcmp("relu", argv[2]) == 0)
            {
                mrelu(argv[3], argv[4]);
            }
            else if (strcmp("tanh", argv[2]) == 0)
            {
                mtanh(argv[3], argv[4]);
            }
            else
            {

                throw std::runtime_error("Enter relu or tanh.\n");
            }
        }
        else if (strcmp("pooling", argv[1]) == 0)
        {
            if (argc != 6)
                throw std::runtime_error("Invalid number of arguments passed.\n");

            if (strcmp("max", argv[2]) == 0)
            {
                mmaxpool(argv[3], argv[4], argv[5]);
            }
            else if (strcmp("average", argv[2]) == 0)
            {
                mavgpool(argv[3], argv[4], argv[5]);
            }
            else
            {

                throw std::runtime_error("Enter max or average.\n");
            }
        }
        else if (strcmp("probability", argv[1]) == 0)
        {
            if (argc != 5)
                throw std::runtime_error("Invalid number of arguments passed.\n");

            if (strcmp("softmax", argv[2]) == 0)
            {
                vsoftmax(argv[3], argv[4]);
            }
            else if (strcmp("sigmoid", argv[2]) == 0)
            {
                vsigmoid(argv[3], argv[4]);
            }
            else
            {

                throw std::runtime_error("Enter softmax or sigmoid.\n");
            }
        }
        else
        {
            throw std::runtime_error("Invalid command passed.\n");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}