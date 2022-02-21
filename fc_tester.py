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
    
def make_test(s,iter):
    a = b = c = s
    m1 = np.random.random((a,b))
    m2 = np.random.random((b,c))
    m3 = np.random.random((a,c))

    m_fc = np.add(np.dot(m1,m2) ,m3)

    mat_to_file(m1,str(s) + "/" + str(iter)  + "/"+ "inputmatrix.txt")
    mat_to_file(m2,str(s) + "/" + str(iter) + "/"+ "weightmatrix.txt")
    mat_to_file(m3,str(s) + "/" + str(iter) + "/"+ "biasmatrix.txt")
    mat_to_file(m_fc,str(s) + "/" + str(iter) + "/"+ "outputmatrix.txt")
    
    
    


def maker(i):
    # for i in range(1,10):
        for j in range(2):
            os.makedirs(os.getcwd()+"/" + str(100*i) + "/" + str(j))
            make_test(100*i,j)


if __name__ == '__main__':
    for i in range(1,3):
        maker(i)
