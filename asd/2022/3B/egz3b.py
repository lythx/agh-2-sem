import heapq
import random

def contains(a, b):
    return a[0] <= b[0] and b[1] <= a[1]

def notcool(a, b):
    return not (contains(a, b) or contains(b, a) or a[1] < b[0] or b[1] < a[0])

print(notcool((38, 44), (44, 52)))  # True

def naive( P ):
    N = len(P)
    for i in range(N):
        for j in range(N):
            #if not (contains(P[i], P[j]) or contains(P[j], P[i]) or P[i][1] < P[j][0] or P[j][1] < P[i][0]):
            if notcool(P[i], P[j]):
                return (i, j)

def styrta( P ):
    n = len(P)
    for i in range(n):
        a, b = P[i]
        P[i] = (a, b, i)
    P.sort(key=lambda x: (x[0], x[1]))
    heap = []
    for i in range(n):
        while heap and heap[0][0] < P[i][0]:
            heapq.heappop(heap)
        if heap:
            b, a, k = heap[0]
            c, d, l = P[i]
            if notcool((a, b), (c, d)):
                return k, l
        heapq.heappush(heap, (P[i][1], P[i][0], P[i][2]))

print(styrta([(11, 20), (21, 28), (28, 64)]))

i = 0
while True:
    if i % 1024 == 0: print(i)
    P = []
    #for _ in range(random.randint(2, 20)):
    for _ in range(3):
        a = random.randint(0, 100)
        b = random.randint(a, 100)
        P.append((a, b))
    res = styrta(P[:])
    # if res != None:
    #     if not notcool(P[res[0]], P[res[1]]):
    #         print("fail", P, res, P[res[0]], P[res[1]])
    if naive(P) != None:
        print("miss", P, naive(P))
    i += 1