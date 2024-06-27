from egz3atesty import runtests
from math import log2
from math import inf


def left(i): return 2 * i + 1
def right(i): return 2 * i + 2
def parent(i): return i // 2 - 1

def snow(T, I):
    points = []
    for a, b in I:
        points.append(a)
        points.append(b)
    points = [0, 10, 5, 20, 7, 12, 15]
    points.sort()
    n = 2**(int(log2(len(points)) + 1)) - 1
    n = 7
    print(n)
    points.extend([T] * (n - len(points)))
    tree = [None] * n

    def tree_create(l, r, i=0, a=-inf, b=inf):
        if l == r:
            return
        m = (l + r) // 2
        tree[i] = [points[m], a, b, 0]
        tree_create(l, m, left(i), a, points[m])
        tree_create(m + 1, r, right(i), points[m], b)

    tree_create(0, n)

    def tree_insert(a, b, i=0):
        if i >= n:
            return
        p = tree[i]
        point, span_a, span_b, _ = p
        if a == span_a and b == span_b:
            p[3] += 1
            return
        if left(i) >= n:
            if a == span_a and b == point:
                p[3] += 1
            elif a == point and b == span_b:
                p[3] += 1
            return
        if b <= point:
            tree_insert(a, b, left(i))
        elif a >= point:
            tree_insert(a, b, right(i))
        else:
            tree_insert(a, point, left(i))
            tree_insert(point, b, right(i))

    for a, b in I:
        tree_insert(a, b)

    def tree_query(query, i=0):
        point, span_a, span_b, count = tree[i]
        print(i, point, span_a, span_b, count)
        if left(i) >= n:
            return count
        if query <= point:
            count += tree_query(query, left(i))
        if query >= point:
            count += tree_query(query, right(i))
        return count

    print([tree_query(x) for x in points])
    # return max([tree_query(x) for x in points])

# zmien all_tests na True zeby uruchomic wszystkie testy
# runtests( snow, all_tests = True )
# a = snow(100, [(3, 10), (0, 5), (20, 30), (25, 35), (26, 26)])
a = snow(21, [(0, 10), (5, 20),  (7, 12), (10, 15)])
print(a)
