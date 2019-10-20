#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : plot.py
# License           : GPL-3.0-or-later
# Author            : Yimin Gu <github.com/ustcpetergu>
# Date              : 2019.10.20
# Last Modified Date: 2019.10.20
from physicsexp.mainfunc import *

# simu
line1 = np.array([float(i) for i in input().split()])
# real
line2 = np.array([float(i) for i in input().split()])
idx = np.array([i for i in range(len(line1))])
plt.plot(idx, line2, color='orange')
plt.plot(idx, line1, color='green')
plt.show()
# simple_plot(idx, line1)
# simple_plot(idx, line2)
# print(line1)
