from egz3atesty import runtests

def snow(T, I):
    n = len(I)
    points = [None] * (2 * n)
    for i in range(n):
        points[2 * i] = (I[i][0], 1)
        points[2 * i + 1] = (I[i][1], -1)
    points.sort(key=lambda x: (x[0], -x[1]))
    height = max_height = 0
    for _, val in points:
        height += val
        max_height = max(max_height, height)
    return max_height

# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( snow, all_tests = True )
