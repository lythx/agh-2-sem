from egz1btesty import runtests
from math import inf
# NIE DZIAŁĄ !!!!!!!!!!!!!!!!!!!!!
def planets( D, C, T, E ):
    n = len(D)
    F = [[inf] * (E + 1) for _ in range(n)]
    for i in range(E + 1):
        F[0][i] = i * C[0]
    j, p = T[0]
    if j > 0:
        F[j][0] = F[0][0] + p
    for i in range(1, n):
        d = D[i] - D[i - 1]
        if d <= E:
            F[i][0] = min(F[i][0], F[i - 1][d])
        for j in range(1, E + 1 - d):
            F[i][j] = F[i - 1][j + d]
        for j in range(1, E + 1):
            F[i][j] = min(F[i][j], F[i][j - 1] + C[i])
        j, p = T[i]
        if j > i:
            F[j][0] = min(F[j][0], F[i][0] + p)
    return min(F[-1])

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( planets, all_tests = True )
