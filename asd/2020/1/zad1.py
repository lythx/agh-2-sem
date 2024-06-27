from zad1testy import runtests


def chaos_index( T ):
    n = len(T)
    T = [(x, i) for i, x in enumerate(T)]
    T.sort(key=lambda x: x[0])
    mx = 0
    for i in range(n):
        mx = max(mx, abs(T[i][1] - i))
    return mx


runtests( chaos_index )
