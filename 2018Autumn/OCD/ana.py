#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
import math


# fin = open('./data.txt', 'r')
# datanum = int(fin.readline())
# data = []
# for i in range(datanum):
#     data.append([int(i) for i in fin.readline().split()][1:])
# print(data)

datafile = './data.txt'
# isUSTC: 1 for USTCers, 0 for other school
isUSTC = np.genfromtxt(datafile, delimiter=' ', usecols=(1,), dtype=int)
isUSTC = 2 - isUSTC
# grade: 1 for grade one, 0 for higher grade
grade = np.genfromtxt(datafile, delimiter=' ', usecols=(2,), dtype=int)
grade = np.array([0 if i > 1 else 1 for i in grade])
isknown = np.genfromtxt(datafile, delimiter=' ', usecols=(3,), dtype=int)
isknown = 2 - isknown
# others: 1 for yes(means bad), 0 for maybe, -1 for no(in good condition)
isselfOCD = np.genfromtxt(datafile, delimiter=' ', usecols=(4,), dtype=int)
isselfOCD = 2 - isselfOCD
isOCDbad = np.genfromtxt(datafile, delimiter=' ', usecols=(5,), dtype=int)
isOCDbad = 2 - isOCDbad
self_condition = np.genfromtxt(datafile, delimiter=' ', usecols=(6, 7, 8, 9, 10, 11), dtype=int)
self_condition = 2 - self_condition
self_condition_sum = np.array([i.sum() for i in self_condition])
test_result = np.genfromtxt(datafile, delimiter=' ', usecols=(i for i in range(12, 40 + 1)), dtype=int)
test_result = 2 - test_result
test_result_sum = np.array([i.sum() for i in test_result])

total = len(isUSTC)
total_ustc = (isUSTC == 1).sum()
print('Total questionnaires: %d' % total)
print('USTC: %d' % total_ustc)
print('non-USTC: %d' % (total - total_ustc))
total_gradeone = (grade == 1).sum()
print('Grade one or lower: %d' % total_gradeone)
print('Grade two or higher: %d' % (total - total_gradeone))
print('Know about OCD: %f' % ((isknown == 1).sum() / total))
print('Know about OCD USTC: %f' % ((isknown[isUSTC == 1] == 1).sum() / total_ustc))
print('Know about OCD non-USTC: %f' % ((isknown[isUSTC == 0] == 1).sum() / (total - total_ustc)))
print('Think self has OCD: %f' % ((isselfOCD == 1).sum() / total))
print('Think self has OCD USTC: %f' % ((isselfOCD[isUSTC == 1] == 1).sum() / total_ustc))
print('Think self has OCD non-USTC: %f' % ((isselfOCD[isUSTC == 0] == 1).sum() / (total - total_ustc)))
print('Think self disturbed by OCD: %f' % ((isOCDbad == 1).sum() / total))
print('Think self disturbed by OCD USTC: %f' % ((isOCDbad[isUSTC == 1] == 1).sum() / total_ustc))
print('Think self disturbed by OCD non-USTC: %f' % ((isOCDbad[isUSTC == 0] == 1).sum() / (total - total_ustc)))

print('Correlation of self_condition: ')
self_condition_cor = np.corrcoef(self_condition.transpose())
print(self_condition_cor)
# you can see all these elems are Positive

print('Correlation of test_result: ')
test_result_cor = np.corrcoef(test_result.transpose())
print(test_result_cor)
# you can see all these elems are also Positive
