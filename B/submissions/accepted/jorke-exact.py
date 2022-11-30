#!/usr/bin/env python3
h,r,d1,d2 = [int(i) for i in input().split()]
print("%.10f" % (h / (1+(d2/d1)**.5)))
