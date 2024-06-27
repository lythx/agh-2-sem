from kolutesty import runtests


def counting_sort(A, k):
    n = len(A)
    B = [None] * n
    C = [0] * k
    for x in A:
        C[x] += 1
    for i in range(1, k):
        C[i] += C[i - 1]
    for i in range(n - 1, -1, -1):
        B[C[A[i]] - 1] = A[i]
        C[A[i]] -= 1
    for i in range(n):
        A[i] = B[i]

# Trzeba zauważyć że kolejność zjadania kubełków nie ma znaczenia,
# zatem szukamy najbardziej optymalnego podzbioru kubełków
def ice_cream(T):
    n = len(T)
    ans = 0
    day_count = 0
    # Kubełki z ilością lodów większą niż ilość dni nie stopią się,
    # zatem na pewno należą do optymalnego podzbioru
    for i in range(n):
        if T[i] >= n:
            # Zamiast tworzyć podzbiór od razu liczę wynik
            # zakładając że zjadam je po kolei tak jak w tablicy
            ans += T[i] - day_count
            day_count += 1
            T[i] = 0
    # Teraz maksymalna wartość tablicy to n - 1 -> można użyć counting sorta
    counting_sort(T, n)
    T.reverse()
    i = 0
    # Zjadam posortowane lody dopóki się nie stopią
    while i < n and T[i] > day_count:
        ans += T[i] - day_count
        day_count += 1
        i += 1
    return ans

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( ice_cream, all_tests = True )
