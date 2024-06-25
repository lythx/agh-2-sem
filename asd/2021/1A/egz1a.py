from egz1atesty import runtests

def snow( S ):
    n = len(S)
    S.sort(reverse=True)
    i = 0
    ans = 0
    while i < n and S[i] - i > 0:
        ans += S[i] - i
        i += 1
    return ans

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( snow, all_tests = False )
