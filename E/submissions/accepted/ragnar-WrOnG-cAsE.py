#!/usr/bin/env python3

a, b = map(int, input().split("/"))

# The minimum possible is (b-1)/b
if a < b - 1:
    print("ImPoSsIbLe")
    exit(0)


# Max average for n:
# (n-1)/2 >= a/b
# n >= 2a/b+!

# n = k * b
# k = n/b >= (2*a/b+1)/b = (2ab + b)/b^2
k = (2 * a + b + b * b - 1) // (b * b)
n = k * b

# n nodes, n-1 edges
# internal id i is at distance i
# (External IDs are +1)
print(n, n - 1)

sum = 0
target = k * a
for i in range(n):
    # make sure we leave distance 1 for the remaining nodes
    d = min(i, target - sum - (n - 1 - i))
    sum += d
    if i > 0:
        # i (with external id i+1) should be at distance d.
        # node with id (d-1) is at distance d.
        print(i + 1, d - 1 + 1)
