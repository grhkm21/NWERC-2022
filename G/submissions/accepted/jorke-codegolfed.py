#!/usr/bin/env python3
p = [*__import__("random").choices("01", k=50), input()]
while p[:50] != p[-50:]: p[-1] != p[-51] and input("? flip\n"), p.append(input("? right\n"))
print("!", len(p) - 100)
