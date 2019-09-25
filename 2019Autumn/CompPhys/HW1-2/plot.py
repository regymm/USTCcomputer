#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt("data.txt", delimiter=" ")
xdata = data[::2]
ydata = data[1:][::2]
plt.scatter(xdata, ydata, marker='+')
# plt.scatter(xdata, ydata, marker='o', c='', edgecolor='blue')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Random number graph of 16807')
plt.savefig('rnggraph.png')
plt.show()
