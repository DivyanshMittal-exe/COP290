import numpy as np
from random import randint
import os
import threading

def mat_to_file(matrix,filename):
    row,col = matrix.shape
    matrix = np.ravel(matrix, order='F')
    file = open(filename, "w+") 
    file.write(str(row)+"\n")
    file.write(str(col)+"\n")
    for e in matrix:
        file.write(str(e)+"\n")
    file.close() 
    
def make_test(s):
    a = b = c = s
    m1 = np.random.random((a,b))
    m2 = np.random.random((b,c))
    m3 = np.random.random((a,c))

    m_fc = np.add(np.dot(m1,m2) ,m3)

    mat_to_file(m1,str(s) +  "/"+ "inputmatrix.txt")
    mat_to_file(m2,str(s) +  "/"+ "weightmatrix.txt")
    mat_to_file(m3,str(s) + "/"+ "biasmatrix.txt")
    mat_to_file(m_fc,str(s) +"/"+ "outputmatrix.txt")
    
    
    


def maker(i):
        os.makedirs(os.getcwd()+"/" + str(10*i))
        make_test(10*i)


if __name__ == '__main__':
    for i in range(5,30):
        maker(i)