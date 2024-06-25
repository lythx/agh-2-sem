from egz1btesty import runtests
from collections import deque

class Node:
  def __init__( self ):
    self.left = None    # lewe poddrzewo
    self.right = None   # prawe poddrzewo
    self.x = None       # pole do wykorzystania przez studentow

def wideentall( T ):
    que: deque[Node] = deque()
    que.append(T)
    max_width = 0
    max_width_level = -1
    level = 0
    # BFS, szukam maksymalnej szerokości, czyli ilości węzłów na jednym poziomie
    while len(que) != 0:
        # >= bo chcę jak najwyższe drzewo
        if len(que) >= max_width:
            max_width = len(que)
            max_width_level = level
        for _ in range(len(que)):
            p = que.popleft()
            if p.left:
                que.append(p.left)
            if p.right:
                que.append(p.right)
        level += 1

    DELETE = -1
    # DFS, szukam najmniejszej ilości krawędzi do usunięcia tak aby drzewo miało
    # wszystkie liście na poziomie max_width_level. DELETE służy do oznaczania
    # poddrzew nie połączonych z nowymi liściami - w tym przypadku
    # należy usunąć najwyższą krawędź
    def dfs(p, level):
        if p is None:
            return 0
        if level == max_width_level:
            delete_count = 0
            if p.left:
                delete_count += 1
            if p.right:
                delete_count += 1
            return delete_count
        # tu level < max_width_level
        left = dfs(p.left, level + 1)
        right = dfs(p.right, level + 1)
        if (left == DELETE or p.left is None) and (right == DELETE or p.right is None):
            return DELETE
        if right == DELETE:
            return left + 1
        if left == DELETE:
            return right + 1
        return left + right

    return dfs(T, 0)


# zmien all_tests na True zeby uruchomic wszystkie testy
runtests( wideentall, all_tests = True )
#
# A = Node()
# B = Node()
# C = Node()
# A.left = B
# A.right = C
# D = Node()
# E = Node()
# B.left = D
# B.right = E
# F = Node()
# E.right = F
# G = Node()
# F.right = G
# print(wideentall(A))
