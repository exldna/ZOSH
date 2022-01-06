n: int
m: int

graph: list
used: list
mt: list


def kuhn(v):

    global n, m
    global graph, used, mt

    if (used[v]):
        return False;

    used[v] = True;

    for vt in graph[v]:
        if mt[vt] == -1 or kuhn(mt[vt]):
            mt[vt] = v
            return True
    
    return False


def main():

    global n, m
    global graph, used, mt

    n, m = map(int, input().split())

    graph = list()

    for _ in range(n):
        s = list(map(lambda v: int(v) - 1, input().split()))[:-1]
        graph.append(s)

    mt = [-1 for _ in range(m)]

    for v in range(n):
        used = [False for _ in range(n)]
        kuhn(v)

    ans = '\n'
    l = 0

    for i, j in enumerate(mt):
        print(i, j)
        if j != -1:
            l += 1
            ans += f'{i + 1} {j + 1}\n'

    print(l, ans)


if __name__ == '__main__':
    main()
