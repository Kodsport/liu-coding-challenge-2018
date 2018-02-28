dx = [-1, 0, 1, 0]
dy = [0, -1, 0, 1]

(W, H) = map(int, raw_input().split())
grid = [raw_input() for _ in range(H)]

Q = []
dist = [(1<<30)]*(5*H*W)
for y in range(H):
    for x in range(W):
        if grid[y][x] == 'M':
            u = (y*W+x)*5 + 4
            Q.append(u)
            dist[u] = 0
d = 0
while Q:
    NQ = []
    while Q:
        u = Q[-1]
        Q.pop()
        if dist[u] > d: continue
        dr = u % 5
        x = (u/5) % W
        y = u/5/W
        if dr < 4:
            if grid[y][x] == '_':
                nx = x + dx[dr]
                ny = y + dy[dr]
                if grid[ny][nx] != '#':
                    nu = (ny*W + nx)*5 + dr
                    if dist[nu] > d:
                        dist[nu] = d
                        Q.append(nu)
            nu = u - dr + 4
            if dist[nu] > d+1:
                dist[nu] = d+1
                NQ.append(nu)
        else:
            for ndr in range(4):
                nx = x + dx[ndr]
                ny = y + dy[ndr]
                if (grid[ny][nx] != '#' and
                    (grid[y][x] != '_' or grid[y-dy[ndr]][x-dx[ndr]] == '#')):
                    nu = (ny*W + nx)*5 + ndr
                    if dist[nu] > d:
                        dist[nu] = d
                        Q.append(nu)
    Q = NQ
    d += 1

for y in range(H):
    d = [dist[(y*W+x)*5+4] for x in range(W)]
    print ' '.join(map(str, (v if v < 1<<30 else -1 for v in d)))
