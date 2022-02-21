import numpy as np
from random import randint

def mat_to_file(matrix,filename):
    row,col = matrix.shape
    matrix = np.ravel(matrix, order='F')
    file = open(filename, "w") 
    file.write(str(col)+"\n")
    file.write(str(row)+"\n")
    for e in matrix:
        file.write(str(e)+"\n")
    file.close() 
    
def make_test():
    s = 10
    e = 100

    a = randint(s, e)
    b = randint(s, e)
    c = randint(s, e)
    m1 = np.random.random((a,b)).astype(np.float32)
    m2 = np.random.random((b,c)).astype(np.float32)
    m3 = np.random.random((a,c)).astype(np.float32)

    m_fc = np.add(np.dot(m1,m2) ,m3)

    mat_to_file(m1,"inputmatrix.txt")
    mat_to_file(m2,"weightmatrix.txt")
    mat_to_file(m3,"biasmatrix.txt")
    mat_to_file(m_fc,"outputmatrix.txt")

if __name__ == '__main__':
    make_test()