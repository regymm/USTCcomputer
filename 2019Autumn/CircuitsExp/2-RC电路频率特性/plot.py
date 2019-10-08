#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : plot.py
# License           : GPL-3.0-or-later
# Author            : Yimin Gu <github.com/ustcpetergu>
# Date              : 2019.10.02
# Last Modified Date: 2019.10.02
# -*- coding: utf-8 -*-

from physicsexp.mainfunc import *
from physicsexp.gendocx import *

# read data
# # 1
# data, data_orig, name = readdata('./data.txt', need=0b111)
# # 2
fin = open('./data.txt', 'r', encoding='utf-8')
f1 = readoneline(fin)
U01 = readoneline(fin)
B1 = readoneline(fin)
A1 = readoneline(fin)
f2 = readoneline(fin)
U02 = readoneline(fin)
A2 = readoneline(fin)
B2 = readoneline(fin)
f3 = readoneline(fin)
U03 = readoneline(fin)
A3 = readoneline(fin)
B3 = readoneline(fin)
fin.close()

# data process
simple_plot(f1, U01, xlab='f/Hz', ylab='U0/V', title='RC低通电路幅频响应', save='11.png')
theta1 = [-math.asin(B1[i]/A1[i]) * 180 / math.pi for i in range(len(f1)) ]
print(theta1[7])
simple_plot(f1, theta1, xlab='f/Hz', ylab='$\\theta$', title='RC低通电路相频响应', save='12.png')

simple_plot(f2, U02, xlab='f/Hz', ylab='U0/V', title='RC高通电路幅频响应', save='21.png')
theta2 = [math.asin(B2[i]/A2[i]) * 180 / math.pi for i in range(len(f2)) ]
print(theta2[7])
simple_plot(f2, theta2, xlab='f/Hz', ylab='$\\theta$', title='RC高通电路相频响应', save='22.png')

simple_plot(f3, U03, xlab='f/Hz', ylab='U0/V', title='RC串并联电路幅频响应', save='31.png')
theta3 = [math.asin(B3[i]/A3[i]) * 180 * (1 if i < 8 else -1) / math.pi for i in range(len(f3)) ]
print(theta3[7])
print(theta3[-1])
simple_plot(f3, theta3, xlab='f/Hz', ylab='$\\theta$', title='RC串并联电路相频响应', save='32.png')
# print(max1, max2, max3)
# simple_plot(f, max1, show=0, issetrange=0, lab='第1个信号', dot='+')
# simple_plot(f, max2, show=0, issetrange=0, lab='第2个信号', dot='*')
# simple_plot(f, max3, show=1, issetrange=0, lab='第3个信号', xlab='f/MHz', ylab='示波器格子数', dot='o',
            # title='三个信号最高点位置随频率变化', save='1.png')

# simple_plot(f, max2 - max1, show=0, issetrange=0, lab='max2-max1', dot='+',
            # xlab='f/Mhz', ylab='最高点间距', title='第1,2个信号间距随频率变化')
# simple_plot(f, max3 - max2, show=1, issetrange=0, lab='max3-max2', dot='*',
            # xlab='f/Mhz', ylab='最高点间距', title='第2,3个信号间距随频率变化', save='2.png')
# simple_plot(f, [math.cos(max2[i] - max1[i]) for i in range(len(f))], show=0, issetrange=0, lab='max2-max1', dot='+',
#             xlab='f/Mhz', ylab='最高点间距', title='第1,2个信号间距随频率变化')
# simple_plot(f, [math.cos(max3[i] - max2[i]) for i in range(len(f))], show=1, issetrange=0, lab='max3-max2', dot='*',
#             xlab='f/Mhz', ylab='最高点间距', title='第2,3个信号间距随频率变化', save='2.png')
# linear regression and plot
# #1
# result = linear_regression(x, y)
# setrange(x, y)
# plt.scatter(x, y, marker='o', color='black', label='原始数据')
# plt.plot(x, result['intercept'] + result['slope'] * x, 'r', label='拟合直线')
# plt.xlabel('')
# plt.ylabel('')
# plt.legend(loc=4)
# plt.title('')
# plt.savefig('pic.png')
# plt.show()

# #2
# use automate tool
# simple_linear_plot(x, y, xlab='x axis', ylab='y axis', title='my pic', save='pic.png')


# generate docx #1
gendocx('gen.docx', '11.png', '12.png', '21.png', '22.png', '31.png', '32.png')

# generate docx #2
# docu = Document()
# docuaddtitle(docu)
# docuappend(docu, './picfull.png', './figure_1.png', './pic.png', result['string'], './picx.png')
# docu.save('gen.docx')


