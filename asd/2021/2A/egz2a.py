from egz2atesty import runtests
from math import log2


def left(i): return 2 * i + 1
def right(i): return 2 * i + 2


def tree_insert(tree, limit, val, i=0):
    n = len(tree)
    l = left(i)
    # liść
    if l >= n:
        tree[i] += val
        # zwracam indeks w oryginalnej tablicy
        return i - (n // 2)
    # schodze w lewo jeśli to możliwe
    if tree[l] + val <= limit:
        ind = tree_insert(tree, limit, val, l)
    else:
        ind = tree_insert(tree, limit, val, right(i))
    # naprawiam minimum po wstawieniu
    tree[i] = min(tree[left(i)], tree[right(i)])
    return ind

def coal( A, T ):
    n = len(A)
    containers = 2**(int(log2(n)) + 1)
    tree = [0] * (2 * containers - 1)
    for a in A[:(n - 1)]:
        tree_insert(tree, T, a)
    return tree_insert(tree, T, A[-1])

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( coal, all_tests = True )
