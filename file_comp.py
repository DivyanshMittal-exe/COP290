f1 = open("outputmatrix.txt")
f2 = open("test_outputmatrix.txt")

l1 = f1.readlines()
l2 = f2.readlines()

for w1,w2 in zip(l1,l2):
    if abs(float(w1) - float(w2)) > 1e-4:
        print("Pthread sucks")
        break
else:
    print("Go pthreads")