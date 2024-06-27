from kolutesty import runtests

def projects(n, L):
    G = [[] for _ in range(n)]
    for u, v in L:
        G[u].append(v)
    n = len(G)
    d = [-1] * n

    def dfs(u):
        d[u] = 1
        for v in G[u]:
            if d[v] == -1:
                dfs(v)
            d[u] = max(d[u], d[v] + 1)

    for u in range(n):
        if d[u] == -1:
            dfs(u)

    return max(d)

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( projects, all_tests = True )
