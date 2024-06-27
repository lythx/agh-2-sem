from zad2testy import runtests
from math import inf

def balance( T ):

    def weight_sum_dfs(u):
        weight = sum(u.weights)
        for v in u.edges:
            weight += weight_sum_dfs(v)
        return weight

    total_weight = weight_sum_dfs(T)
    min_diff = inf
    ans = None

    def find_target_dfs(u, parent_edge, parent_edge_weight):
        nonlocal min_diff, ans
        weight = sum(u.weights)
        for v, edge, w in zip(u.edges, u.ids, u.weights):
            weight += find_target_dfs(v, edge, w)
        weight_diff = abs(weight - (total_weight - weight - parent_edge_weight))
        if abs(weight_diff) < min_diff:
            min_diff = abs(weight_diff)
            ans = parent_edge
        return weight

    find_target_dfs(T, None, inf)
    return ans


runtests( balance )
