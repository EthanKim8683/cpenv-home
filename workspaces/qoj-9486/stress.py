import sys


T = int(3e5)
print(T)
t = 0
for i in range(8000 + 1)[::-1]:
    for j in range(i, 8000 + 1)[::-1]:
        print(j, i)
        t += 1
        if t == T:
            sys.exit(0)
