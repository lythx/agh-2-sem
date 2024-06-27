def partition(A, p, r):
    x = A[r]
    i = p - 1
    for j in range(p, r):
        if A[j] <= x:
            i += 1
            A[i], A[j] = A[j], A[i]
    A[i + 1], A[r] = A[r], A[i + 1]
    return i + 1


def quickselect(A, p, r, k):
    if p == r:
        return A[p]
    q = partition(A, p, r)
    if q == k:
        return A[q]
    elif k < q:
        return quickselect(A, p, q - 1, k)
    else:
        return quickselect(A, q + 1, r, k)


def Median(T):
    n = len(T)
    n2 = n**2
    arr = [None] * n2
    for i in range(n):
        for j in range(n):
            arr[i * n + j] = T[i][j]
    mid = n2 // 2
    left = mid - n // 2
    quickselect(arr, 0, n2 - 1, left)
    right = mid + n // 2
    quickselect(arr, left + 1, n2 - 1, right)
    k = 0
    for i in range(1, n):
        for j in range(i):
            T[i][j] = arr[k]
            k += 1
    for i in range(n):
        T[i][i] = arr[k]
        k += 1
    for i in range(n):
        for j in range(i + 1, n):
            T[i][j] = arr[k]
            k += 1
    for x in T:
        print(x)
    return T

Median([[2,3,5, -10],
        [7,11,13, -42],
        [-727, 17,19,23],
        [1000, 100000, 1032123, 2]])
