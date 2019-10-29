#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : plot.py
# License           : GPL-3.0-or-later
# Author            : Yimin Gu <github.com/ustcpetergu>
# Date              : 2019.10.27
# Last Modified Date: 2019.10.27
from physicsexp.mainfunc import *

dat = np.array([float(i) for i in input().split()])
logdat = np.log(dat)
N = np.array(range(1, 1 + len(dat)))
logN = np.log(N)
result = simple_linear_plot(logN, logdat, xlab='lnN', ylab='ln<r^2>', title='double logarithmic graph')
print(result)

