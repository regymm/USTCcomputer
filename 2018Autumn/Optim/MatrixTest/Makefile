test.out: mklmain.cpp mymatrix.cpp
	g++ -o mkltest.out mklmain.cpp -lmkl_rt -L/opt/intel/mkl/lib/intel64 -L/opt/intel/lib/intel64 -I/opt/intel/mkl/include
	g++ -o mytest.out mymatrix.cpp $(CPPFLAGS) -fopenmp

clean:
	-rm *.out *.o 
.PHONY: clean
