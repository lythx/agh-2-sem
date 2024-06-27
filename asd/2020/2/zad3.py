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
        return f'({self.a}, {self.b}) <r:{self.red}, g:{self.green}, b:{self.blue}>, LAZY: ({self.lazy_left}, {self.lazy_right})'


def left(i): return 2 * i + 1
def right(i): return 2 * i + 2


def tree_create(tree, i, dummy):
    if tree[i] is not None:
        tree[i].green = tree[i].b - tree[i].a + 1
        if tree[i].b == dummy:
            tree[i].green -= 1
        return tree[i].a, tree[i].b
    a, _ = tree_create(tree, left(i), dummy)
    _, b = tree_create(tree, right(i), dummy)
    tree[i] = Node(a, b)
    tree[i].green = b - a + 1
    if tree[i].b == dummy:
        tree[i].green -= 1
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


def tree_query(tree, a, b, i=0, lazy_count=0, debug=False):
    p = tree[i]
    inter = intersection(a, b, p.a, p.b)

    if inter is None:
        if lazy_count > 0:
            flip(p, lazy_count)
            p.lazy_left += lazy_count
            p.lazy_right += lazy_count
        return

    p.lazy_left += lazy_count
    p.lazy_right += lazy_count
    a, b = inter

    if a == p.a and b == p.b:
        flip(p, lazy_count + 1)
        p.lazy_left += 1
        p.lazy_right += 1
        return

    tree_query(tree, a, b, left(i), p.lazy_left, debug)
    p.lazy_left = 0
    tree_query(tree, a, b, right(i), p.lazy_right, debug)
    p.lazy_right = 0

    l = tree[left(i)]
    r = tree[right(i)]
    p.green = l.green + r.green
    p.red = l.red + r.red
    p.blue = l.blue + r.blue

def lamps(n, T):
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
    tree_create(tree, 0, n)

    mx = 0
    for a, b in T:
        tree_query(tree, a, b)
        mx = max(mx, tree[0].blue)
    return mx

runtests( lamps )
