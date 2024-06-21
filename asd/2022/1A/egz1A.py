from egz1Atesty import runtests
from queue import PriorityQueue
from math import inf

def gold(G,V,s,t,r):
    n = len(V)
    dist = [inf] * n
    dist[s] = 0
    pq = PriorityQueue()
    pq.put((0, s))
    while not pq.empty():
        d, u = pq.get()
        for v, cost in G[u]:
            if dist[v] > d + cost:
                dist[v] = d + cost
                pq.put((dist[v], v))

    dist2 = [inf] * n
    dist2[t] = 0
    pq.put((0, t))
    while not pq.empty():
        d, u = pq.get()
        for v, cost in G[u]:
            new_cost = 2 * cost + r + d
            if dist2[v] > new_cost:
                dist2[v] = new_cost
                pq.put((dist2[v], v))

    return -max([V[u] - dist[u] - dist2[u] for u in range(n)])



# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( gold, all_tests = True )
