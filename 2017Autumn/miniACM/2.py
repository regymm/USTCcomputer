#!/usr/bin/env python
class Solution:
    def IsPopOrder(self, pushV, popV):
        length = len(pushV)
        mystack = [0 for i in range(length + 1)]
        num = 0
        iin = 0
        iout = 0
        mystack[0] = -1
        # print mystack
        # print pushV
        # print popV
        # print '----'
        while iout < length:
            # print mystack
            if iin < length:
                if pushV[iin] == popV[iout]:
                    iin += 1
                    iout += 1
                    continue
            if popV[iout] == mystack[num]:
                iout += 1
                num -= 1
                continue
            num += 1
            if iin < length:
                mystack[num] = pushV[iin]
            else:
                return False
            iin += 1
        if mystack[num] != -1:
            return False
        else:
            return True
t = Solution()
print t.IsPopOrder([1,3,2,4,5,6,7,8,9], [1,3,2,4,5,6,7,8,9])
print t.IsPopOrder([1,2,3,4,5], [3,5,4,1,2])
print t.IsPopOrder([1], [1])
print t.IsPopOrder([2,1], [2,1])
print t.IsPopOrder([1,2,3], [3,1,2])
print t.IsPopOrder(['a', 'b', 'c'], ['c', 'b', 'a'])
#pass
