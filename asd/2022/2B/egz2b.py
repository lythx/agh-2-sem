from egz2btesty import runtests
from math import inf

def parking(X,Y):
    n = len(X)
    m = len(Y)
    F = [[inf] * m for _ in range(n)]
    for i in range(m):
        F[0][i] = abs(X[0] - Y[i])
    for i in range(1, n):
        for j in range(1, m):
            a = F[i][j - 1] + abs(X[i] - Y[j]) - abs(X[i] - Y[j - 1])
            b = F[i - 1][j - 1] + abs(X[i] - Y[j])
            F[i][j] = min(a, b)
    return min(F[n - 1])

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( parking, all_tests = True )
