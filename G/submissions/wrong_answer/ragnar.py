#!/usr/bin/env python3

# Move 1000 steps to set things to 0
for _ in range(1000):
    x = int(input())
    if x == 1:
        print("? flip", flush=True)
        input()

    print("? right", flush=True)

# Set one to 1
print("? flip")
input()

# Move to the right while 0.
ans = 1
print("? right")
while input() == "0":
    print("? right")
    ans += 1

print("! %d" % ans)
