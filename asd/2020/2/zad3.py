from zad3testy import runtests
from math import ceil, log2

class Node:
    def __init__(self, a, b):
        self.a = a
        self.b = b
        self.red = 0
        self.green = 0
        self.blue = 0
        self.lazy_left = 0
        self.lazy_right = 0

    def __repr__(self):
        return f'({self.a}, {self.b}) <r:{self.red}, g:{self.green}, b:{self.blue}>'


def left(i): return 2 * i + 1
def right(i): return 2 * i + 2


def tree_create(tree, i):
    if tree[i] is not None:
        tree[i].green = 1
        return tree[i].a, tree[i].b
    a, _ = tree_create(tree, left(i))
    _, b = tree_create(tree, right(i))
    tree[i] = Node(a, b)
    tree[i].green = b - a + 1
    return a, b


def intersection(a, b, x, y):
    l = max(a, x)
    r = min(b, y)
    if r < l:
        return None
    return l, r


def flip(p, count):
    arr = [p.green, p.blue, p.red]
    p.green = arr[count % 3]
    p.blue = arr[(count + 1) % 3]
    p.red = arr[(count + 2) % 3]

def tree_query(tree, a, b, i=0, lazy_count=0):
    p = tree[i]
    inter = intersection(a, b, p.a, p.b)
    p.lazy_right += lazy_count
    p.lazy_left += lazy_count
    if inter is None:
        return
    a, b = inter
    if a == p.a and b == p.b:
        flip(p, lazy_count + 1)
        p.lazy_left += 1
        p.lazy_right += 1
        return
    tree_query(tree, a, b, left(i), p.lazy_left)
    p.lazy_left = 0
    tree_query(tree, a, b, right(i), p.lazy_right)
    p.lazy_right = 0
    l = tree[left(i)]
    r = tree[right(i)]
    p.green = l.green + r.green
    p.red = l.red + r.red
    p.blue = l.blue + r.blue

def lamps(n, T):
    m = len(T)
    points = []
    for a, b in T:
        points.append(Node(a, a))
        points.append(Node(b, b))
    points.append(Node(0, 0))
    points.append(Node(n - 1, n - 1))
    points.sort(key=lambda x: x.a)
    temp = [points[0]]
    for p in points[1:]:
        if p.a != temp[-1].a:
            temp.append(p)
    points = temp
    for i in range(1, len(points)):
        if points[i].a - points[i - 1].b > 1:
            points.append(Node(points[i - 1].b + 1, points[i].a - 1))
    points.sort(key=lambda x: x.a)
    k = 2**ceil(log2(len(points)))
    points.extend(Node(n, n) for _ in range(k - len(points)))
    tree = [None] * (k - 1)
    tree.extend(points)
    tree_create(tree, 0)

    mx = 0
    brute_tab = brute(n , T)
    i = 0
    print(tree)
    for a, b in T:
        tree_query(tree, a, b)
        mx = max(mx, tree[0].blue)
        print(brute_tab[i], mx, a, b, tree)
        i += 1
    print(mx)
    return mx

def brute(n, T):
    arr = [0] * n
    mx = [-1]
    for a, b in T:
        for i in range(a, b + 1):
            arr[i] = (arr[i] + 1) % 3
        mx.append(max(mx[-1], arr.count(2)))
    return mx[1:]


# print(lamps(8, [(0, 4), (2, 6)]))
# runtests( lamps )

lamps(20, [(11, 13), (4, 4), (2, 3), (5, 5), (14, 18), (9, 13), (7, 10), (9, 11), (7, 10), (9, 11), (14, 14), (5, 9), (16, 19), (6, 10), (16, 19), (14, 18), (16, 18), (4, 7), (8, 12), (2, 3)])
# 13
