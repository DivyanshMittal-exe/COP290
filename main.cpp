// Submission by Divyansh Mittal, 2020CS10342

#include <iostream>
#include <string.h>
#include "lib/Plain/Matrix.h"
#include "lib/pThread/pMatrix.h"
#include "lib/Plain/Vector.h"

// Implementation of Fully Connected Matrix
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

void pmfc(std::string input_file, std::string weight_matrix, std::string bias_matrix, std::string output_file)
{
    try
    {
        pMatrix m_in(input_file);
        pMatrix m_wgt(weight_matrix);
        pMatrix m_bias(bias_matrix);

        pMatrix m_out = (m_in * m_wgt) + m_bias;
        m_out.print(output_file);
    }
    catch (const std::exception &e)
    {
        throw;
    }
}

// Implementation of Relu
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

// Implementation of Tanh

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

// Implementation of Maxpool

void mmaxpool(std::string input_file, std::string Stride, std::string output_file)
{
    try
    {
        Matrix<float> m_in(input_file);
        Matrix<float> m_out = m_in.max_pooling(atoi(Stride.c_str()));
        m_out.print(output_file);
    }
    catch (const std::exception &e)
    {
        throw;
    }
}

// Implementation of Avg Pooling

void mavgpool(std::string input_file, std::string Stride, std::string output_file)
{

    try
    {
        Matrix<float> m_in(input_file);
        Matrix<float> m_out = m_in.avg_pooling(atoi(Stride.c_str()));
        m_out.print(output_file);
    }
    catch (const std::exception &e)
    {
        throw;
    }
}

// Implementation of Softmax

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

// Implementation of sigmoid
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
        // Throw error if less arguments
        if (argc <= 1)
            throw std::runtime_error("Function not given. Please pass a function and input output parameters\n");

        // Throw error if no files specified
        if(argc == 2)
            throw std::runtime_error("Pass input output parameters too and not just name of the function.\n");

        if (strcmp("fullyconnected", argv[1]) == 0)
        {
            if (argc != 6)
                throw std::runtime_error("Invalid number of arguments passed.\n");

            else
                mfc(argv[2], argv[3], argv[4], argv[5]);
        }
        else if (strcmp("pfullyconnected", argv[1]) == 0)
        {
            if (argc != 6)
                throw std::runtime_error("Invalid number of arguments passed.\n");

            else
                pmfc(argv[2], argv[3], argv[4], argv[5]);
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
                //Error if nothing matchers

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
                //Error if nothing matchers

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
                //Error if nothing matchers
                throw std::runtime_error("Enter softmax or sigmoid.\n");
            }
        }
        else
        //Error if nothing matchers
        {
            throw std::runtime_error("Invalid command passed.\n");
        }
    }

    //Print the error to cerr
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}