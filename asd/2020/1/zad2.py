from zad2testy import runtests
from collections import deque

def robot(L, A, B):
    m = len(L)
    n = len(L[0])
    # wynik mnożymy razy 5
    TURN_TIME = 9
    MOVE_TIME = (12, 8, 6)
    # DIRECTIONS[dir] = (direction, di, dj, turn_time)
    DIRECTIONS = (
        ((0, 0, 1, 0), (1, 1, 0, TURN_TIME), (2, 0, -1, 2 * TURN_TIME), (3, -1, 0, TURN_TIME)),
        ((1, 1, 0, 0), (2, 0, -1, TURN_TIME), (3, -1, 0, 2 * TURN_TIME), (0, 0, 1, TURN_TIME)),
        ((2, 0, -1, 0), (3, -1, 0, TURN_TIME), (0, 0, 1, 2 * TURN_TIME), (1, 1, 0, TURN_TIME)),
        ((3, -1, 0, 0), (0, 0, 1, TURN_TIME), (1, 1, 0, 2 * TURN_TIME), (2, 0, -1, TURN_TIME))
    )
    visited = [[[[False] * n for _ in range(m)] for _ in range(3)] for _ in range(4)]
    visited[0][0][A[1]][A[0]] = True
    q = deque()
    # direction, speed, i, j, timeout
    q.append((0, -1, A[1], A[0], 1))
    time = 0
    while len(q) != 0:
        for _ in range(len(q)):
            direction, speed, i, j, timeout = q.popleft()
            if timeout != 1:
                q.append((direction, speed, i, j, timeout - 1))
                continue
            if j == B[0] and i == B[1]:
                return time * 5
            for new_dir, di, dj, turn_time in DIRECTIONS[direction]:
                new_speed = min(speed + 1, 2) if direction == new_dir else 0
                if (0 <= i + di < m) and (0 <= j + dj < n) and L[i + di][j + dj] == ' ' \
                        and not visited[new_dir][new_speed][i + di][j + dj]:
                    visited[new_dir][new_speed][i + di][j + dj] = True
                    new_timeout = turn_time + MOVE_TIME[new_speed]
                    q.append((new_dir, new_speed, i + di, j + dj, new_timeout))
        time += 1
    return None


# runtests( robot )


def MergeSort(A):
    n=len(A)
    if n>1:
        i=n//2
        L=A[:i]
        R=A[i:]
        MergeSort(L)
        MergeSort(R)
        j=k=0
        while j<i and k<n-i:
            if L[j][1]<=R[k][1]:
                A[j+k]=L[j]
                j+=1
            else:
                A[j+k]=R[k]
                k+=1
        while j<i:
            A[j+k]=L[j]
            j+=1
        while k<n-i:
            A[j+k]=R[k]
            k+=1


A = [(1, 1),(6, 6) ,(43, 43), (-324, -324)]
MergeSort(A)
print(A)