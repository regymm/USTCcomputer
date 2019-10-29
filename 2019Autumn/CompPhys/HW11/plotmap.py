#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : plotmap.py
# License           : GPL-3.0-or-later
# Author            : Yimin Gu <github.com/ustcpetergu>
# Date              : 2019.10.27
# Last Modified Date: 2019.10.28
from physicsexp.mainfunc import *

x = np.array([float(i) for i in input().split()])
y = np.array([float(i) for i in input().split()])
simple_plot(x, y, xlab='x', ylab='y', title='GSAW result visualized')

