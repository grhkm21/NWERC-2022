#!/usr/bin/env python3
[(int(input()) and (print("? flip"), input()), print("? right")) for _ in range(5000)]
int(input()) or print("? flip"), input()
print("! %d" % next(i + 1 for i, (_, b) in enumerate((print("? right"), input()) for _ in range(5000)) if int(b)))
