#!/bin/bash
# File              : run.sh
# License           : GPL-3.0-or-later
# Author            : Yimin Gu <github.com/ustcpetergu>
# Date              : 2019.10.01
# Last Modified Date: 2019.10.01

gcc ./hw7.c -o a.out
echo "Task 1:"
./a.out task1 < ./data.TXT | sed s'/.$//' > data1.csv
echo "Task 2:"
./a.out task2 < ./data.TXT | sed s'/.$//' > data2.csv
