import random

N = 5000
print(N, random.randint(1, 100))
print(*[random.randint(1, 5000) for _ in range(N)])
