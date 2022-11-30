from decimal import *

getcontext().prec = 100

# abstract into two blocks, air and water
# let height of water be x
# then water    CoM has position x / 2       and mass x * d_w
# and  air      CoM has position (h + x) / 2 and mass (h - x) * d_a
# and  combined CoM has position c           and mass x * d_w + (h - x) * d_a

h, r, d_a, d_w = map(Decimal, input().split())


def calc(x):
    new_weight = (x * x * d_w + (h + x) * (h - x) * d_a) / 2
    new_mass = x * d_w + (h - x) * d_a
    return new_weight / new_mass


# ternary search
l = 0
r = h
for _ in range(200):
    m1, m2 = (2 * l + r) / 3, (l + 2 * r) / 3
    if calc(m1) > calc(m2):
        l = m1
    elif calc(m1) < calc(m2):
        r = m2
    else:
        l, r = m1, m2

print(l)
