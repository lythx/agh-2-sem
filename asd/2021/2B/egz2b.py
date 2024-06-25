from egz2btesty import runtests
from queue import PriorityQueue
from math import inf

def magic(C):
    n = len(C)
    dp = [-1] * n
    dp[0] = 0
    for i in range(n):
        if dp[i] == -1:
            continue
        R = C[i]
        g = R[0]
        for k, w in R[1:]:
            if w == -1:
                continue
            take = g - k
            new_gold = dp[i] + take
            if take <= 10 and new_gold >= 0:
                dp[w] = max(dp[w], new_gold)
    return dp[n - 1]


# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( magic, all_tests = True )
