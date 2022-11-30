#!/usr/bin/env python3
h,r,d1,d2 = [int(i) for i in input().split()]

def value(x):
    return (x*d2*x/2 + (h-x)*d1*(h+x)/2) / (x*d2 + (h-x)*d1)

lower, upper = 0,h
for _ in range(0, 500):
    mid1 = (2*lower+upper)/3
    mid2 = (lower+2*upper)/3
    val1 = value(mid1)
    val2 = value(mid2)
    if val1 < val2:
        upper = mid2
    else:
        lower = mid1

print("%.10f" % lower)
