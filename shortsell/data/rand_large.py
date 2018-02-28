import random

N = 100000
print(N, random.randint(1, 100))
print(*[random.randint(1, 100000) for _ in range(N)])
