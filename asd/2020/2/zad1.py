from zad1testy import runtests

def binary_search(arr, val, left=0):
    right = len(arr)
    while left < right:
        mid = left + (right - left) // 2
        if val <= arr[mid][0]:
            right = mid
        else:
            left = mid + 1
    return left

def intuse( I, x, y ):
    n = len(I)
    I = [(a, b, i) for i, (a, b) in enumerate(I)]
    I.sort(key=lambda x: (x[0], -x[1]))
    visited = {y: 2}

    def dfs(u, last_ind):
        ind = binary_search(I, u, last_ind)
        res = []
        flag = False
        while ind < n and I[ind][0] == u:
            v = I[ind][1]
            if u == v:
                if flag:
                    res.append(ind)
                    ind += 1
                continue
            if v > y:
                ind += 1
                continue
            if v not in visited:
                visited[v] = 1
                dfs_res = dfs(v, ind)
                if dfs_res:
                    res += dfs_res
                    flag = True
                    visited[v] = 2
            elif visited[v] == 2:
                res.append(ind)
                flag = True
            ind += 1
        if not flag:
            return []
        return res + [last_ind]

    visited[x] = 1
    ans = dfs(x, 0)
    return [I[i][2] for i in ans[:-1]]



# intuse([[3, 4], [2, 5], [1, 3], [4, 6], [1, 4]], 1 ,6)
runtests( intuse )
