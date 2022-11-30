import math
l,r=map(int,input().split())
x=input().split()
def y(c):
 a=0
 for i,s in enumerate(x):
  if len(s)==8 or s[0]==c:a=math.gcd(a,i+l)
 if a==0:a=r+1
 return a
print(y('F'), y('B'))
