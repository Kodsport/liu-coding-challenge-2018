def gcd(a, b):
    if b == 0: return (a, 1, 0)
    (d, x, y) = gcd(b, a % b)
    return (d, y, x - a/b*y)

n = int(raw_input())
V = [0] + map(int, raw_input().split())
t = int(raw_input())

init = []
for i in range(1, n+1):
    while V[i] <= t:
        init.append('fill %d' % i)
        init.append('transfer %d 0' % i)
        t -= V[i]

d = 0
coeffs = [0]*(n+1)
for i in range(1, n+1):
    (d, x, y) = gcd(d, V[i])
    for j in range(1, i):
        coeffs[j] *= x
    coeffs[i] += y
    if t % d == 0:
        break

#print coeffs

for i in range(1, n+1):
    for j in range(1, n+1):
        while 2*coeffs[i] >= V[i] and 2*coeffs[j] <= -V[j]:
            coeffs[i] -= V[j]
            coeffs[j] += V[i]

#print coeffs

if t % d:
    print 'impossible'
else:
    basic = []
    have = 0
    cur = [0]*(n+1)
    cap = sum(V)
    def transfer(i, j):
        trans = min(cur[i], V[j]-cur[j])
        if i != j and trans:
            cur[i] -= trans
            cur[j] += trans
            basic.append('transfer %d %d' % (i, j))

    while have != d:
        for i in range(1, n+1):
            while coeffs[i] < 0 and have >= V[i]:
                for j in range(1, n+1):
                    transfer(j, i)
                assert cur[i] == V[i]
                have -= V[i]
                coeffs[i] += 1
                cur[i] = 0
                basic.append('discard %d' % i)
            while coeffs[i] > 0 and have + V[i] <= cap:
                for j in range(1, n+1):
                    transfer(i, j)
                assert cur[i] == 0
                have += V[i]
                coeffs[i] -= 1
                cur[i] = V[i]
                basic.append('fill %d' % i)
    for i in range(1, n+1):
        if cur[i]:
            basic.append('transfer %d 0' % i)
    for L in init:
        print L
    for _ in range(t/d):
        for L in basic:
            print L
