#!/usr/bin/env python3
(n, k) = list(map(int, input().split()))
v = list(map(int, input().split()))

max_val = ans = 0
for i in range(n):
    v[i] = 100*v[i] + k*i
    max_val = max(max_val, v[i])
    ans = max(ans, max_val - v[i])

print(max(ans-k, 0))
