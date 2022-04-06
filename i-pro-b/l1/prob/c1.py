n: int
m: int

graph: list
match: list
used: list


def read():

    global n, m
    global graph, match

    m, n = map(int, input().split())
    graph = list()

    read_list = lambda: list(map(lambda v: int(v) - 1, input().split()))

    for _ in range(m):
        graph.append(read_list()[1:])

    match = read_list()


def control():

    global n, m
    global graph, match, used

    orient = [list() for _ in range(m + n)]

    for i, k in enumerate(graph):
        for j in k:
            orient[i].append(j + m)

    for i, j in enumerate(match):
        k = j + m
        if k in orient[i]:
            orient[i].remove(k)
            orient[k].append(i)

    used = [False for _ in range(n + m)]

    def bfs(v):
        used[v] = True
        for it in orient[v]:
            if not used[it]:
                bfs(it)

    for i in range(m):
        if match[i] == -1:
            bfs(i)


def answer():

    global used

    left = list()

    for i in range(m):
        if not used[i]:
            left.append(i)

    right = list()

    for i in range(m, m + n):
        if used[i]:
            right.append(i)

    print(len(left) + len(right))
    print(len(left), end=' ')
    for i in left:
        print(i + 1, end=' ')
    print()
    print(len(right), end=' ')
    for i in right:
        print(i + 1 - m, end=' ')



if __name__ == '__main__':
    read()
    control()
    answer()
