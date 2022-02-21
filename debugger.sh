if [ $1 = "debug" ];
then

rm -rf Subtask1TestCasesV1.1/a1a.test.outputmatrix.txt Subtask1TestCasesV1.1/a2a.test.outputmatrix.txt Subtask1TestCasesV1.1/a2b.test.outputmatrix.txt Subtask1TestCasesV1.1/a3a.test.outputmatrix.txt Subtask1TestCasesV1.1/a3b.test.outputmatrix.txt Subtask1TestCasesV1.1/a4a.test.outputvector.txt Subtask1TestCasesV1.1/a4b.test.outputvector.txt

./yourcode.out fullyconnected Subtask1TestCasesV1.1/a1a.inputmatrix.txt Subtask1TestCasesV1.1/a1a.weightmatrix.txt Subtask1TestCasesV1.1/a1a.biasmatrix.txt Subtask1TestCasesV1.1/a1a.test.outputmatrix.txt

if !(diff -w -q Subtask1TestCasesV1.1/a1a.outputmatrix.txt Subtask1TestCasesV1.1/a1a.test.outputmatrix.txt)
    then
        echo "a1a is wrong"
        exit
    fi
echo "a1a is correct"

./yourcode.out pfullyconnected Subtask1TestCasesV1.1/a1a.inputmatrix.txt Subtask1TestCasesV1.1/a1a.weightmatrix.txt Subtask1TestCasesV1.1/a1a.biasmatrix.txt Subtask1TestCasesV1.1/a1a.test.outputmatrix.txt

if !(diff -w -q Subtask1TestCasesV1.1/a1a.outputmatrix.txt Subtask1TestCasesV1.1/a1a.test.outputmatrix.txt)
    then
        echo "pthread a1a is wrong"
        exit
    fi
echo "pthread a1a is correct"

./yourcode.out activation relu Subtask1TestCasesV1.1/a2a.inputmatrix.txt Subtask1TestCasesV1.1/a2a.test.outputmatrix.txt

if !(diff -w -q Subtask1TestCasesV1.1/a2a.outputmatrix.txt Subtask1TestCasesV1.1/a2a.test.outputmatrix.txt)
    then
        echo "a2a is wrong"
        exit
    fi
echo "a2a is correct"

./yourcode.out activation tanh Subtask1TestCasesV1.1/a2b.inputmatrix.txt Subtask1TestCasesV1.1/a2b.test.outputmatrix.txt

if !(diff -w -q Subtask1TestCasesV1.1/a2b.outputmatrix.txt Subtask1TestCasesV1.1/a2b.test.outputmatrix.txt)
    then
        echo "a2b is wrong"
        exit
    fi
echo "a2b is correct"

./yourcode.out pooling max Subtask1TestCasesV1.1/a3a.inputmatrix.txt 2 Subtask1TestCasesV1.1/a3a.test.outputmatrix.txt

if !(diff -w -q Subtask1TestCasesV1.1/a3a.outputmatrix.txt Subtask1TestCasesV1.1/a3a.test.outputmatrix.txt)
    then
        echo "a3a is wrong"
        exit
    fi
echo "a3a is correct"


./yourcode.out pooling average Subtask1TestCasesV1.1/a3b.inputmatrix.txt 2 Subtask1TestCasesV1.1/a3b.test.outputmatrix.txt

if !(diff -w -q Subtask1TestCasesV1.1/a3b.outputmatrix.txt Subtask1TestCasesV1.1/a3b.test.outputmatrix.txt)
    then
        echo "a3b is wrong"
        exit
    fi
echo "a3b is correct"

./yourcode.out probability softmax Subtask1TestCasesV1.1/a4a.inputvector.txt Subtask1TestCasesV1.1/a4a.test.outputvector.txt

if !(diff -w -q Subtask1TestCasesV1.1/a4a.outputvector.txt Subtask1TestCasesV1.1/a4a.test.outputvector.txt)
    then
        echo "a4a is wrong"
        exit
    fi
echo "a4a is correct"

./yourcode.out probability sigmoid Subtask1TestCasesV1.1/a4b.inputvector.txt Subtask1TestCasesV1.1/a4b.test.outputvector.txt

if !(diff -w -q Subtask1TestCasesV1.1/a4b.outputvector.txt Subtask1TestCasesV1.1/a4b.test.outputvector.txt)
    then
        echo "a4b is wrong"
        exit
    fi
echo "a4b is correct"

elif [ $1 = "pdebug" ];
then

./yourcode.out pthread fullyconnected pTestCase/inputmatrix.txt pTestCase/weightmatrix.txt pTestCase/biasmatrix.txt pTestCase/test_outputmatrix.txt

python utils/file_comp.py pTestCase/outputmatrix.txt pTestCase/test_outputmatrix.txt

else

make clean

make 

./yourcode.out fullyconnected pTestCase/inputmatrix.txt pTestCase/weightmatrix.txt pTestCase/biasmatrix.txt pTestCase/test_outputmatrix.txt
python utils/file_comp.py pTestCase/outputmatrix.txt pTestCase/test_outputmatrix.txt

rm -rf pTestCase/test_outputmatrix.txt

./yourcode.out pthread fullyconnected pTestCase/inputmatrix.txt pTestCase/weightmatrix.txt pTestCase/biasmatrix.txt pTestCase/test_outputmatrix.txt
python utils/file_comp.py pTestCase/outputmatrix.txt pTestCase/test_outputmatrix.txt

rm -rf pTestCase/test_outputmatrix.txt

make clean
make mkl

./yourcode.out mkl fullyconnected pTestCase/inputmatrix.txt pTestCase/weightmatrix.txt pTestCase/biasmatrix.txt pTestCase/test_outputmatrix.txt
python utils/file_comp.py pTestCase/outputmatrix.txt pTestCase/test_outputmatrix.txt

rm -rf pTestCase/test_outputmatrix.txt

make clean
make oblas

./yourcode.out oblas fullyconnected pTestCase/inputmatrix.txt pTestCase/weightmatrix.txt pTestCase/biasmatrix.txt pTestCase/test_outputmatrix.txt
python utils/file_comp.py pTestCase/outputmatrix.txt pTestCase/test_outputmatrix.txt

rm -rf pTestCase/test_outputmatrix.txt

make clean



fi