# COP290 Subtask 3

  - [How to run the code](#how-to-run-the-code)
  - [Implementation](#implementation)
  - [Implementation of the libaudioAPI](#implementation-of-the-libaudioAPI)


## How to run the code
Once we have the libaudio.so, simply run the make file by `make` command for compilation of the code. If you want to compile the "libaudio.so" file from source, run `make lib`.

Then write the command you want to run, it is of the form `./youcode.out input_fcc_features.txt outputfile.txt`
eg - 

``` 
./yourcode.out mfcc_features/ca4d5368_nohash_5.txt out.txt 
```

The output would be appended in the file **out.txt**. If the file is not present, a new file is created

Requirement - the variable MKL_BLAS_PATH in environment is set appropriately ($export MKL_BLAS_PATH=/usr/include/mkl). One can also edit the MakeFile to set the MKL_BLAS_PATH appropriately.


## Implementation

We are using our mkl implementation of fully connected layer from stage 2 for this assignment. We have made a libaudio.cpp file which is the cpp file for the library. libaudio.so is the .so file for the library which can be used in other programs after linking and using the -laudio flag.

In main.cpp we use the libaudioAPI function from the libaudio.so file to get the top 3 indices and their probabilities

### Implementation of the libaudioAPI

The function libaudio implementation typedefines a structure with an integer label and a float prob for probability by the name of pred_t

The function 
```
pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred);

```

takes in an input of char*, which is an array of char for the input file name and a pointer for a pred_t array of size 3. This array contains the top 3 probabilites and labels.

The audio sounds it can recognise are
  {"silence","unknown","yes","no","up","down","left","right","on","off","stop","go"}

Int label of pred_t contains the corresponding index of audio recognised.

