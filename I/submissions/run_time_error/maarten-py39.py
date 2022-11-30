#!/usr/bin/env python3
# @EXPECTED_RESULTS@: ACCEPTED,RUN_TIME_ERROR
# Beautiful two-liner, too bad that we don't support Python 3.9 😅 (https://2022.nwerc.eu/systems/)
print(*(999999 if t not in l else __import__("math").gcd(*(s + i for i, x in enumerate(l.split()) if t in x))
        for s, l in [(int(input().split()[0]), input())] for t in "FB"))
