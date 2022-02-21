    # sed ' s/convolution_without_threading/convolution_mkl/' include/func/conv/handle.h > include/func/conv/handle_mkl.h

    # sed ' s/\\n>/\\n\(mkl\) >/' interpreter.cpp > interpreter_temp.cpp
    # sed ' s/handle.h/handle_mkl.h/' interpreter_temp.cpp > interpreter_mkl.cpp
    g++ -o ipl_mkl test.cpp -L${MKLROOT}/lib/intel64 -Wl,--no-as-needed -lmkl_intel_ilp64 -lmkl_gnu_thread -lmkl_core -lgomp -lpthread -lm -ldl