# Path to NVCC compiler, since its likely not on $PATH
NVCC=/usr/local/cuda/bin/nvcc

# Xcompiler flag passes comma separated list of flag to the
# GCC/G++ compiler. Optimization flags can be pass directly
# to NVCC. O3 enables vectorization on for-loops.
NVCC_FLAGS=-arch=sm_61 -rdc=true -std=c++11  -Xcompiler -fopenmp -Xcompiler -Wall -g
FILES=driver.c gn.cu array.c util.c
INCLUDE1=/usr/include/R
INCLUDE2=/usr/include/R/R_ext
all:
	$(NVCC) $(NVCC_FLAGS) -I$(INCLUDE1) -I$(INCLUDE2) $(FILES) -lRmath -lgomp -o retnfit_cuda

clean:
	rm retnfit_cuda

c_driver:
	gcc -g driver.c gn.c array.c util.c -I$(INCLUDE1) -lRmath -lm -fopenmp -o retnfit_cpu
