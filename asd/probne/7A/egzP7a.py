from egzP7atesty import runtests
from math import inf

def create_residual_network(G, R):
    n = len(G)
    for u in range(n):
        for v in G[u]:
            # Domyślnie ustawiamy flow krawędzi na 1
            R[u][v] = 1
            # Flow krawędzi wstecznej na 0 o ile nie była już przetworzona
            if R[v][u] is None:
                R[v][u] = 0


def add_back_edges(G, R):
    n = len(G)
    for u in range(n):
        for v in G[u]:
            # Krawędzie wsteczne mają na początku flow 0
            if R[v][u] == 0:
                G[v].append(u)

# DFS z pominięciem krawędzi z flowem 0
def dfs(G, R, parent, visited, u):
    for v in G[u]:
        if not visited[v] and R[u][v] != 0:
            parent[v] = u
            visited[v] = True
            dfs(G, R, parent, visited, v)

# Augmenting path - ścieżka powiększająca
def find_augmenting_path(G, R, s, t, parent):
    n = len(G)
    visited = [False] * n
    visited[s] = True
    dfs(G, R, parent, visited, s)
    # Jeśli ścieżka powiększająca istnieje to doszliśmy do początku
    return visited[t]

def ford_fulkerson(G, s, t):
    n = len(G)
    # R - sieć residualna, None oznacza brak połączenia czyli brak przepływu
    R = [[None] * n for _ in range(n)]
    create_residual_network(G, R)
    add_back_edges(G, R)
    parent = [None] * n
    max_flow = 0
    # While wykonuje sie dopóki istnieje ścieżka powiększająca
    # find_augmenting_path daje dostęp do tej ścieżki
    # za pomocą tablicy parent
    while find_augmenting_path(G, R, s, t, parent):
        current_flow = inf
        u = t
        # Po ścieżce przechodzimy używając tablicy parent
        # Znajdujemy o ile można zwiększyć flow
        while u != s:
            current_flow = min(current_flow, R[parent[u]][u])
            u = parent[u]
        max_flow += current_flow
        u = t
        # Update ścieżki z nowym flow
        while u != s:
            v = parent[u]
            R[v][u] -= current_flow
            R[u][v] += current_flow
            u = parent[u]
    return max_flow

def akademik(T):
    n = len(T)
    # Pierwszy wierzchołek - źródło
    # Następne n wierzchołków - studenci
    # Następne n wierzchołków - akademiki
    # Ostatni wierzchołek - ujście
    G = [[] for _ in range(2 * n + 2)]
    G[0] = [x + 1 for x in range(n)]
    for u in range(n):
        for v in T[u]:
            if v is not None:
                G[u + 1].append(v + 1 + n)
        # ujście z każdego akademika
        G[u + 1 + n].append(2 * n + 1)
    empty = 0
    for x in T:
        if x == (None, None, None):
            empty += 1
    max_flow = ford_fulkerson(G, 0, 2 * n + 1)
    return n - max_flow - empty

runtests ( akademik )
