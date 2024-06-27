from zad3testy import runtests
from heapq import heapify, heappushpop

def kintersect(A, k):
    n = len(A)
    A = [(a, b, i) for i, (a, b) in enumerate(A)]
    A.sort()
    heap = [(b, a, i) for a, b, i in A[:k]]
    heapify(heap)
    max_width = heap[0][0] - A[k - 1][0]
    max_width_ind = k - 1
    for ind in range(k, n):
        a, b, i = A[ind]
        heappushpop(heap, (b, a, i))
        if max_width < heap[0][0] - a:
            max_width = heap[0][0] - a
            max_width_ind = ind

    heap = [(b, a, i) for a, b, i in A[:k]]
    heapify(heap)
    for a, b, i in A[k:(max_width_ind + 1)]:
        heappushpop(heap, (b, a, i))
    return [i for _, _, i in heap]

runtests(kintersect)
