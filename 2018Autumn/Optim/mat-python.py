#!/usr/bin/env python3
import numpy as np
import math
import sys
import random
import time

if __name__ == '__main__':
    if len(sys.argv) == 4 and sys.argv[1] == 'gen':
        with open("randMatrix.txt", "w") as f:
            for i in range(int(sys.argv[2])):
                for j in range(int(sys.argv[3])):
                    f.write(str(random.random()) + ' ')
                f.write('\n')
        sys.exit(0)


