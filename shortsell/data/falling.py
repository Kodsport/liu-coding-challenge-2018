import random

N = 1000
print(N, random.randint(1, 100))
print(*[(N - i) * 50 + random.randint(1, 100) for i in range(N)])
