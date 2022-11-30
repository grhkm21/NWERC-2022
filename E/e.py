import sys
from fractions import Fraction
from collections import Counter
from math import gcd, sqrt, floor

print = lambda *args: sys.stdout.write(' '.join(map(str, args)) + '\n')

a, b = map(int, input().split('/'))
g = gcd(a, b)
a //= g
b //= g

if a < b - 1:
    print("impossible")

elif a == b - 1:
    # star graph
    print(b, b - 1)
    for i in range(2, b + 1):
        print(1, i)

else:
    d = 10**6 // b
    a *= d
    b *= d

    # now a / b has b closest to 10^6
    # we want b nodes with sum of dist = a

    # first build chain of k nodes where k(k - 1) / 2 <= a
    # then remaining (b - k) nodes have sum of dist a - k(k - 1) / 2
    # this has to be between (b - k) and k(b - k)
    lim = floor((1 + sqrt(1 + 8 * a)) / 2)

    for k in range(1, lim + 1):
        rem = a - k * (k - 1) // 2

        if b - k <= rem <= k * (b - k):
            # build dist
            arr = [1] * (b - k)
            rem -= b - k

            for i in range(b - k):
                if rem == 0:
                    break
                max_pos = min(rem, k - 1)
                arr[i] += max_pos
                rem -= max_pos

            # print length
            print(b, b - 1)
            # print(Counter(arr))

            # print chain
            for i in range(2, k + 1):
                print(i - 1, i)

            # print remaining
            for i in range(b - k):
                print(i + k + 1, arr[i])

            break

    else:
        raise RuntimeError(f"Cannot find solution for {a // d} / {b // d}")
