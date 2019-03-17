/*

- **Real Cases: My Stupid Experiences**

- Python. Program runs slower after using multithreading.

  Solution: Python's multithreading is 'fake' due to GIL and only useful when I/O is intense. Replace with multitasking accelerates the program. 

- Python & Linux. Want to generate 1M random phone number to test hash. Write one line of Python code in a script, call this one million times, `for i in seq 1 1000000; do python ./randomphone.py >> randomphone.txt; done`, extremely low performance.

  Solution: Most of the time is spent on creating and destroying processes, which is a big cost.

- Memory. Bench a compression software, compress a ~1G file on HDD. >5 times speedup on the second run. 

  Reason: File loaded to memory, no need to read from HDD on the second run, bench inaccurate. 

- Python. A function 

*/