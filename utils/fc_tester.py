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
    # s = 10
    # e = 100
    n = 1000
    # a = randint(s, e)
    # b = randint(s, e)
    # c = randint(s, e)
    a = n
    b = n
    c = n
    m1 = np.random.random((a,b)).astype(np.float32)
    m2 = np.random.random((b,c)).astype(np.float32)
    m3 = np.random.random((a,c)).astype(np.float32)

    m_fc = np.add(np.dot(m1,m2) ,m3)
    base = "testcases/" + str(n)
    mat_to_file(m1, base + "/inputmatrix.txt")
    mat_to_file(m2, base + "/weightmatrix.txt")
    mat_to_file(m3, base + "/biasmatrix.txt")
    mat_to_file(m_fc, base + "/outputmatrix.txt")

if __name__ == '__main__':
    make_test()