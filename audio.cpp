#include <string>
#include <iostream>
#include "libaudio.h"

//I am storing a matrix as a array of doubles (Column Major format)
//For a matrix I am storing the dimension in a pair (col,row)



int main(int argc, char *argv[])
{
     try
    {
        if (argc == 1)
        {
            // No arguments given
            throw "Invalid format. No arguments given. Check out README for valid format.";
        }else if (argc == 3){
            
            predict_audio(argv[1],argv[2]);
        }else {
             throw "Invalid format. Correct format is as follows - ./yourcode.out mkl fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt";
        }

    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
