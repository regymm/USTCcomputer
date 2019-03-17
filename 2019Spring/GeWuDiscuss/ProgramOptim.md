# Program Optimizations(CSAPP Chapter 5, 6)

**古宜民**

**2019.3**

[TOC]

Ref：《深入理解计算机系统》,吴俊敏计算机系统详解课程PPT



## Previous



## Chap. 5 Code Optimization

### General useful optimizations

​	You or **the compiler** should do regardless of processor/compiler

- **Code Motion** 

  - Reduce frequency with which computation performed:
    - If it will always produce same result
    - Especially moving code out of loop

  ```c
    void set_row(double *a, double *b, long i, long n)
    {
    	long j;
    	for(j = 0; j < n; j++)
    		a[n * i + j] = b[j];
    }
  ```

  gcc -Og version: n*j calculated each loop (line 0x7, 0xa)

  ```assembly
    0000000000000000 <set_row>:
       0:   b8 00 00 00 00          mov    $0x0,%eax
       5:   eb 19                   jmp    20 <set_row+0x20>
       7:   49 89 c8                mov    %rcx,%r8
       a:   4c 0f af c2             imul   %rdx,%r8
       e:   49 01 c0                add    %rax,%r8
      11:   f2 0f 10 04 c6          movsd  (%rsi,%rax,8),%xmm0
      16:   f2 42 0f 11 04 c7       movsd  %xmm0,(%rdi,%r8,8)
      1c:   48 83 c0 01             add    $0x1,%rax
      20:   48 39 c8                cmp    %rcx,%rax
      23:   7c e2                   jl     7 <set_row+0x7>
      25:   f3 c3                   repz retq
    
  ```

  gcc -O1 version: n*j calculated only once, stored in %rdx (line 0x5, 0x9)

  ```assembly
  0000000000000000 <set_row>:
     0:   48 85 c9                test   %rcx,%rcx
     3:   7e 20                   jle    25 <set_row+0x25>
     5:   48 0f af d1             imul   %rcx,%rdx
     9:   48 8d 14 d7             lea    (%rdi,%rdx,8),%rdx
     d:   b8 00 00 00 00          mov    $0x0,%eax
    12:   f2 0f 10 04 c6          movsd  (%rsi,%rax,8),%xmm0
    17:   f2 0f 11 04 c2          movsd  %xmm0,(%rdx,%rax,8)
    1c:   48 83 c0 01             add    $0x1,%rax
    20:   48 39 c1                cmp    %rax,%rcx
    23:   75 ed                   jne    12 <set_row+0x12>
    25:   f3 c3                   repz retq
  
  ```

  gcc -O3 version: use ```xor %eax,%eax ``` instead of ```mov $0x0,%eax```

  gcc -O3 version: (about 4-times longer code, I can't understand)

- **Reduction in Strength**

  - Replace costly operation with simpler one (Utility machine dependent)

  Examples:

  Shift, add instead of multiply, divide ```16*x```=>```x<<4```. Compilers will do this. 

  Recognize sequence products

  ```c
  for (i = 0; i < n; i++) {
    int ni = n*i;
    for (j = 0; j < n; j++)
      a[ni + j] = b[j];
  }
  ```

  ```c
  int ni = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      a[ni + j] = b[j];
    ni += n;
  }
  ```

- **Share Common Subexpressions**

  Reuse Expressions. Example:

  Three multiplications

  ```c
  /* Sum neighbors of i,j */
  up =    val[(i-1)*n + j  ];
  down =  val[(i+1)*n + j  ];
  left =  val[i*n     + j-1];
  right = val[i*n     + j+1];
  sum = up + down + left + right;
  ```

  One multiplication

  ```c
  long inj = i*n + j;
  up =    val[inj - n];
  down =  val[inj + n];
  left =  val[inj - 1];
  right = val[inj + 1];
  sum = up + down + left + right;
  ```

  GCC will do this with -O1

### Optimization Blockers

- **Limitations of Optimizing Compilers**
  - Operate under fundamental constraint: Must not cause any change in program behavior (Except Undefined Behaviours)
  - Behavior that may be obvious to the programmer can  be obfuscated by languages and coding styles: variable type ranges are bigger than what you use them for.
  - Most analysis is performed only within procedures: Whole-program analysis is too expensive. Let along different files. 
  - Most analysis is based only on static information: Runtime input cannot be predicted\
  - Conservative all the time!

- **Procedure calls**

  `strlen()`executed each loop. Can compiler move it out of loop? 

  ```c
  void lower(char *s)
  {
    size_t i;
    for (i = 0; i < strlen(s); i++)
      if (s[i] >= 'A' && s[i] <= 'Z')
        s[i] -= ('A' - 'a');
  }
  ```

  - Functions may have side-effects.
  - May not return same value for given arguments
  - Compilers treat them as blackboxes. 

  Use inline function. Do it your own. 

  Another example:

  ```c
  int counter = 0;
  int f(){
      return counter++;
  }
  
  int func1(){
      return f() + f() + f() + f();
  }
  int func2(){
      return 4 * f();
  }
  ```

- **Memory aliasing**

  func2 is faster due to less memory references. Can func1 be optimized to func2 ?

  ```c
  void func1(int *xp, int *yp)
  {
      *xp += *yp;
      *xp += *yp;
  }
  void func2(int *xp, int *yp)
  {
      *xp += 2 * *yp;
  }
  ```

  Nobody said `xp != yp` 

  - **Aliasing**: Two different memory references specify single location

    - Easy to have happen in C: Allow address arithmetic, direct access storage structures 

    - Get in habit of introducing local variables

      Accumulating within loops.

      **Your way of telling compiler not to check for aliasing**

  An implicit example:

  ```c
  /* Sum rows is of n X n matrix a
     and store in vector b  */
  void sum_rows1(double *a, double *b, long n) {
      long i, j;
      for (i = 0; i < n; i++) {
  	b[i] = 0;
  	for (j = 0; j < n; j++)
  	    b[i] += a[i*n + j]; // b[i] updated each loop, bad efficiency
      }
  }
  void sum_rows2(double *a, double *b, long n) {
      long i, j;
      for (i = 0; i < n; i++) {
  		double val = 0;
  		for (j = 0; j < n; j++)
  		    val += a[i*n + j]; // Less memory refencing here
      	b[i] = val;
      }
  }
  ```

  These are **not** same: each b[i] update affects program behavior. Compilers cannot optimize that. 

  ```c
  double A[9] = 
    { 0,   1,   2,
      4,   8,  16},
     32,  64, 128};
  double B[3] = A+3;
  sum_rows1(A, B, 3);
  ```

  

### Exploiting Instruction-Level Parallellism

- **Superscalar Processor**

  - Definition: A superscalar processor can issue and execute **multiple instructions in one cycle**. The instructions are retrieved from a sequential instruction stream and are usually scheduled dynamically.

- **Piplined Functional Units**

  - Divide computation into stages

  - Pass partial computations from stage to stage

  - Stage i can start on new computation once values passed to i+1

    Instructions take >1 cycle, but can be pipelined.

    ***Instruction  Latency  Cycles/Issue***

    **Load / Store  4  1** //need 1 cycle to issue instruction, and it will last for 4 cycles to complete

    **Integer Multiply  3  1**

    **Integer/Long Divide  3-30  3-30**

    **Single/Double FP Multiply  5  1**

    **Single/Double FP Add  3  1**

    **Single/Double FP Divide  3-15  3-15**

  Example: complete 3 multiplications in 7 cycles, even though each requires 3 cycles

  ```c
  long mult_eg(long a, long b, long c) {
      long p1 = a*b;
      long p2 = a*c;
      long p3 = p1 * p2;
      return p3;
  }
  ```

  ![1552264003979](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552264003979.png)

  |         | **Time** |          |          |          |            |            |            |
  | ------- | -------- | -------- | -------- | -------- | :--------- | ---------- | ---------- |
  |         | 1        | 2        | 3        | 4        | 5          | 6          | 7          |
  | Stage 1 | **a\*b** | **a\*c** |          |          | **p1\*p2** |            |            |
  | Stage 2 |          | **a\*b** | **a\*c** |          |            | **p1\*p2** |            |
  | Stage 3 |          |          | **a\*b** | **a\*c** |            |            | **p1\*p2** |

  **Visualizing Operations**

  ```assembly
  .L519:		# Loop:
  	imull	(%rax,%rdx,4), %ecx	# t = t * d[i]
  	addq	$1, %rdx	# i++
  	cmpq	%rdx, %rbp	# Compare length:i
  	jg	.L519	# If >, goto Loop
  ```

  ![1552267850694](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552267850694.png)![1552267916805](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552267916805.png)

  3 Iterations combined:(Resource Limited)

  ![1552267977402](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552267977402.png)![1552268299944](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552268299944.png)

  Find & Elimiante **critical path**!

- **Loop enrolling**

  ```c
  for (i = 0; i < limit; i+=2) {
  	x = (x OP d[i]) OP d[i+1];
  }
  ```

  ![1552268324558](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552268324558.png)

  Performance increased.

  Can this be used in multiplication? Why not? Data Dependency: those `addl`s are connected

- **Reassociation**

  ```c
  #define OP *
  x = (x OP d[i]) OP d[i+1];	
  x = x OP (d[i] OP d[i+1]);
  ```

  Data dependency broke, parallelism enhanced.

  ![1552268751056](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552268751056.png)

- **Seperate accumulators**

  Two independent “streams” of operations, parallelism enhanced.

  ```c
  for (i = 0; i < limit; i+=2) {
  	acc0 = acc0 OP data[i];
      acc1 = acc1 OP data[i+1];
  }
  ```

- **Register spliting**

  No enough registers, accumulators stored in stack and frequeny memory referencing.

- **Use vector instructions**

  ![1552265311980](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552265311980.png)

### Conditionals

- **Challenge**

  Instruction Control Unit must work well ahead of Execution Unit to generate enough operations to keep EU busy

  When encounters conditional branch, cannot reliably determine where to continue fetching

- **Branch Prediction**

  **Guess** which way branch will go
  **Begin** executing instructions at predicted position, but don’t actually modify register or memory data

- **Misprediction**

  - Invalidate fetched instructions
  - Reload correct instructions (reload pipeline)
  - Cost multiple clock cycles(44 cycles on Intel Core i7). Can be major performance limiter

- **Don't Care Too Much**

  - `for(i = 0; i < 100; i++)` Only the last prediction is wrong

  - Write code suitable for implementation with **Conditional Moves**(calculate both results before, and return the right one), "functional" style

    - Only 50% prediction rate, CPE 14.50

      ```c
      /* Rearrange two vectors so that for each i, b[i] >= a[i] */
      void minmax1(int a[], int b[], int n) {
      	int i;
      	for (i = 0; i < n; i++) {
      		if (a[i] > b[i]) {
      			int t = a[i];
      			a[i] = b[i];
      			b[i] = t;
      		}
      	}
      }
      ```

    - Conditional moves used, CPE 5.0

      ```c
      /* Rearrange two vectors so that for each i, b[i] >= a[i] */
      void minmax2(int a[], int b[], int n) {
      	int i;
      	for (i = 0; i < n; i++) {
      		int min = a[i] < b[i] ? a[i] : b[i];
      		int max = a[i] < b[i] ? b[i] : a[i];
      		a[i] = min;
      		b[i] = max;
      	}
      }
      ```

### Profiling

- **Tools**

  - Observation: Generate assembly code
  - Measurement: cycle counter, Unix tool `gprof`

- Example

  ![1552265021045](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552265021045.png)

  ![1552265060158](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552265060158.png)

  Single call(sort_words) use 87% of time

![1552265116179](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552265116179.png)

Iter first: Use iterative function to insert elements into linked list
Causes code to slow down
Iter last: Iterative function, places new entry at end of list
Tend to place most common words at front of list
Big table: Increase number of hash buckets
Better hash: Use more sophisticated hash function
Linear lower: Move strlen out of loop

- **Amdahl’s Law**
  - Total time = (1-a)T + aT
    Component optimizing takes aT time.
    Improvement is factor of k, then:
    T_new = T_old[(1-a) + a/k]
    Speedup = T_old/T_new = 1/ [(1-a) + a/k]
    Maximum Achievable Speedup (k = Inf) = **1/(1-a)**

### Advice

- **Good compiler and flags**
- **Don’t do anything stupid**
  - Watch out for hidden algorithmic inefficiencies
  - Write compiler-friendly code
    Watch out for optimization blockers:  procedure calls & memory references
  - Look carefully at innermost loops (where most work is done)
- Tune code for machine

## Chap. 6 Memory

### Storage technologies and trends

- **RAM**

  ![1552790673400](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552790673400.png)

- **Nonvolatile**

  ROM, NAND, ...

- **Access Main Memory**

  Bus: a collection of parallel wires that carry address, data, and control signals. Shared by devices

  Memory bus

  Load operation `movl A,%eax`

  ![1552791090698](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791090698.png)

  ![1552791114325](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791114325.png)

  ![1552791153996](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791153996.png)

  Store operation `movl %eax,A`

  ![1552791196871](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791196871.png)

  ![1552791215775](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791215775.png)

  ![1552791238022](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791238022.png)

- **Hard Disk Drive**

  ![1552791458243](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791458243.png)

  Taccess  =  Tavg seek +  Tavg rotation + Tavg transfer 

  ~2500 times slower than DRAM

  Logical disk blocks

  I/O Bus

  ![1552791563046](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791563046.png)

  Read HDD sector

  ![1552791625187](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791625187.png)

  ![1552791641450](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791641450.png)

  ![1552791654456](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552791654456.png)

- **Trend**

  DRAM and disk performance are lagging behind CPU performance.

  SRAM roughly keeping up.

  Gap between DRAM and disk and CPU performance widening.

### Locality

- In a program with good **temporal locality**, a memory location
  that is referenced once is likely to be referenced again multiple times in the near
  future. 

- In a program with good **spatial locality**, if a memory location is referenced
  once, then the program is likely to reference a nearby memory location in the near
  future.

- Programs with good locality run faster. Modern computer systems are designed to exploit locality.

- Both **references to program data** and **instruction fetches** have locality

- Example: 

  ```c
  sum = 0;
  for (i = 0; i < n; i++)
  	sum += a[i];
  return sum;
  ```

  Array a has good spatial locality(stride-1 reference pattern)

  Accumulator sum has good temporal locality(refered in each loop)

  Instruction: The for loop executed in sequential memory order(spatial), and executed multiple times(temporal).

### Memory Hierachy

- Fundemental hardware and software properties complement each other.
- Storage devices get slower, bigger, and cheaper going from top to bottom

- **An example**

  ![1552792405981](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552792405981.png)

### Caches

- **Cache**:  a small, fast storage device that acts as a staging area for the data objects stored in a larger, slower device

- ![1552793025405](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552793025405.png)

- **Cache Hits**

- **Cache Misses**

  Fetch a block from lower level. May *replace* an existing block (require a good replacement policy)

  - **Kinds**
  - *Compulsary miss (cold miss)* Won't occur after warmed up. 
  - *Conflict miss* Cache is enough, but different blocks mapped to a same cache block, so keep missing.
  - *Capacity miss* Working set exceeded cache capacity. Cache too small. 

- Example: ubiquity of caches

  ![1552793944688](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552793944688.png)

- **Conclusion**

  - Caching works, because of locality
  - Maintaining locality is becoming more important as the memory gaps widened.

### Cache Memory in brief

- **Cache between CPU and DRAM**
  - L1, L2, L3 cache. SRAM
  - Miss rate: L1 3-10% , L2 <1%
  - Hit time: L1 one CPU cycle, L2 3-8 cycles
  - Miss penalty: 25-100 cycles DRAM

- **Write Cache-friendly Code**

  ```c
  int sumarrayrows(int a[M][N])
  {
      int i, j, sum = 0;
  
      for (i = 0; i < M; i++)
          for (j = 0; j < N; j++)
              sum += a[i][j];
      return sum;
  } // ~1/4 miss
  int sumarraycols(int a[M][N])
  {
      int i, j, sum = 0;
  
      for (j = 0; j < N; j++)
          for (i = 0; i < M; i++)
              sum += a[i][j];
      return sum;
  } // All miss
  ```

### The Memory Mountain

Two-dimensional function of read throughput versus temporal and spatial locality

```c
/* The test function */
void test(int elems, int stride) {
    int i, result = 0; 
    volatile int sink; 

    for (i = 0; i < elems; i += stride)
	result += data[i];
    sink = result; /* So compiler doesn't optimize away the loop */
}

/* Run test(elems, stride) and return read throughput (MB/s) */
double run(int size, int stride, double Mhz)
{
    double cycles;
    int elems = size / sizeof(int); 

    test(elems, stride);                     /* warm up the cache */
    cycles = fcyc2(test, elems, stride, 0);  /* call test(elems,stride) */
    return (size / stride) / (cycles / Mhz); /* convert cycles to MB/s */
}
```

Stride: spatial locality

Size: temperal locality

![1552795868102](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552795868102.png)

Ridges of temporal locality

![1552796089433](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552796089433.png)

A slope of spatial locality

![1552796118666](C:\Users\petergu\AppData\Roaming\Typora\typora-user-images\1552796118666.png)

### Example: Matrix-Matrix Multiplication

## Others

- **Real Cases: My Stupid Experiences**

  - Python. Program runs slower after using multithreading.

    Solution: Python's multithreading is 'fake' due to GIL and only useful when I/O is intense. Replace with multitasking accelerates the program. 

  - Python & Linux. Want to generate 1M random phone number to test hash. Write one line of Python code in a script, call this one million times, `for i in seq 1 1000000; do python ./randomphone.py >> randomphone.txt; done`, extremely low performance.

    Solution: Most of the time is spent on creating and destroying processes, which is a big cost.

  - Memory. Bench a compression software, compress a ~1G file on HDD. >5 times speedup on the second run. 

    Reason: File loaded to memory, no need to read from HDD on the second run, bench inaccurate. 

  - Python. A function 

- **Other Aspects and Advice**

  - Find out what is slow (Bad function, huge amout I/O, nested loops,  repeatous work, ...)
  - Better algorithm and datastructure
  - Better intepreter (Pypy, ...)
  - Faster language (Python modules rewriten in C/C++)
  - Parallel, multithreading/multiprocessing
  - GPU instead of CPU
  - Use library (BLAS, MKL, ...), Never use your own implementation
  - ...