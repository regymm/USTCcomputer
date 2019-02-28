#!/usr/bin/env python3
import math
import dis
def foo(i, length, thres):
    j = i
    while j < length:
        j += 1


def fooslow(i, length, thres):
    for j in range(i, length):
        pass

print("dis foo:")
dis.dis(foo)
print("dis fooslow:")
dis.dis(fooslow)
