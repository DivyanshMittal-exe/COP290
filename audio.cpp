#include <string>
#include <iostream>
#include "libaudio.h"
#include <fstream>


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
            std::string audios[] = {"silence","unknown","yes","no","up","down","left","right","on","off","stop","go"};
            pred_t prediction[3];
            libaudioAPI(argv[1],prediction);
            std::ofstream outfile;
            outfile.open(argv[2] , std::ios_base::app | std::ios_base::out);
            outfile << argv[1] << " ";
            outfile << audios[prediction[0].label] << " " << audios[prediction[1].label] << " " << audios[prediction[2].label] << " " ;
            outfile << prediction[0].prob << " "<< prediction[1].prob << " " << prediction[2].prob << " ";
            outfile << std::endl;
            outfile.close();

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
