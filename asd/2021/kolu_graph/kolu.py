from kolutesty import runtests

def swaps( disk, depends ):
    G = depends
    n = len(G)
    d = [-1] * n

    def dfs(u):
        d[u] = 0
        for v in G[u]:
            cost = 0 if disk[u] == disk[v] else 1
            if d[v] == -1:
                dfs(v)
            d[u] = max(d[u], d[v] + cost)

    for u in range(n):
        if d[u] == -1:
            dfs(u)
    mx = -1
    mx_start = None
    for u in range(n):
        if mx < d[u]:
            mx = d[u]
            mx_start = disk[u]
        if mx == d[u] and mx_start != disk[u]:
            mx += 1
            mx_start = None
    return mx

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( swaps, all_tests = True )
# swaps(['B', 'A', 'B', 'A', 'B', 'A', 'B', 'A', 'B', 'A'], [[1], [], [1, 4, 7], [1, 7], [1], [1, 2, 4], [2, 4, 5], [1], [1, 2], [3, 4]])

