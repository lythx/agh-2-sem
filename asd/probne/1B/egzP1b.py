from egzP1btesty import runtests 
from queue import PriorityQueue
from math import inf

def turysta( G, D, L ):
    E = G
    a = D
    b = L
    n = max(E, key=lambda x: x[1])[1] + 1
    G = [[] for _ in range(n)]
    for u, v, t in E:
        G[u].append((v, t))
        G[v].append((u, t))
    dist = ([inf] * n, [inf] * n, [inf] * n, [inf] * n, [inf] * n)
    dist[0][a] = 0
    pq = PriorityQueue()
    pq.put((0, a, 0))
    while not pq.empty():
        d, u, count = pq.get()
        if u == b:
            if count == 4:
                return d
            continue
        if count == 4:
            continue
        new_c = count + 1
        for (v, t) in G[u]:
            new_d = d + t
            if dist[new_c][v] > new_d:
                dist[new_c][v] = new_d
                pq.put((new_d, v, new_c))
    return -1

runtests ( turysta )