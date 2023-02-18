def mul(A, B):
    return [[max(A[i][z] + B[z][j] for z in range(k)) for j in range(k)] for i in range(k)]

def mul_vec(A, v, offs=0):
    return [max(v[i], max(A[i][z] + v[z] + offs for z in range(k))) for i in range(k)]

(n, k, a, b) = map(int, raw_input().split())
t = map(int, raw_input().split())
d = [[map(int, raw_input().split()) for _ in range(k)]]
for i in range(k):
    for j in range(k):
        d[0][i][j] += t[i]

while 1<<len(d) <= n:
    d.append(mul(d[-1], d[-1]))

def poss(target):
    nb = 0
    res = [t[i] - target*(a+b) for i in range(k)]
    while 2<<nb <= n:
        res = mul_vec(d[nb], res, -target*a*(1<<nb))
        nb += 1
    nn = n - (1<<nb)
    nb = 0
    while nn:
        if nn % 2:
            res = mul_vec(d[nb], res, -target*a*(1<<nb))
        nb += 1
        nn /= 2
    return max(res) > 0

lo = 0
hi = 400
while hi-lo > 1e-8:
    m = (lo+hi)/2.0
    if poss(m): lo = m
    else: hi = m

print lo
