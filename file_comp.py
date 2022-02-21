import sys
if __name__=="__main__":
    f1 = open(sys.argv[1])
    f2 = open(sys.argv[2])

    l1 = f1.readlines()
    l2 = f2.readlines()

    for w1,w2 in zip(l1,l2):
        if abs(float(w1) - float(w2)) > 1e-4:
            print("Files differ")
            break
    else:
        print("Files are the same")