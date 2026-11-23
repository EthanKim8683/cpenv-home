import math
import random


R = 1000
N = 120
K = 120
C = 999
print(f"{R} {N} {K} {C}")
A = list(sorted(random.random() * 2 * math.pi for _ in range(N)))
for e in A:
    print(f"{e:.4f}")
