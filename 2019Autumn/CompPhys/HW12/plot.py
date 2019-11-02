#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : plot.py
# License           : GPL-3.0-or-later
# Author            : Yimin Gu <github.com/ustcpetergu>
# Date              : 2019.10.27
# Last Modified Date: 2019.10.29
from physicsexp.mainfunc import *
import pyqtgraph as pg

Rarr = []
mainarr = []
flag = 0
with open ('data.txt') as f:
    for line in f:
        if flag % 2:
            mainarr.append(np.array([float(i) for i in line.split()]))
        else:
            Rarr.append(float(line))
        flag = flag + 1

pg.plot([1, 2, 3], [3, 2, 1])

# print(Rarr)
# print('----')
# print(mainarr)
# for i in range(len(Rarr)):
    # for j in mainarr[i]:
        # plt.scatter([Rarr[i]], [j], s=0.1, color='black')
# plt.show()




# dat = np.array([float(i) for i in input().split()])
# logdat = np.log(dat)
# N = np.array(range(1, 1 + len(dat)))
# logN = np.log(N)
# result = simple_linear_plot(logN, logdat, xlab='lnN', ylab='ln<r^2>', title='double logarithmic graph')
# print(result)

