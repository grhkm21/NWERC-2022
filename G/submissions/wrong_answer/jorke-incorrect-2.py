#!/usr/bin/env python3
flip  = lambda : int(input("? flip\n"))
left  = lambda : int(input("? left\n"))
right = lambda : int(input("? right\n"))

# This submission only fails in the range [3027,3185].
numbers = [508, 1517, 3026, 5001]
a = [int(input())]
for num in numbers:
    for i in range(num-len(a)):
        a.append(right())
    a[-1] = flip()
    a.reverse()
    left,right=right,left
    for i in range(1,len(a)):
        if right() != a[i]:
            print("!",i)
            exit()
