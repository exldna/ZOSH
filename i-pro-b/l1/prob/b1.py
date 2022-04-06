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

    n = int(input())
    name = input()
    m = len(name)

    if n < m:
        print("NO")
        return

    graph = list()

    for _ in range(n):
        cube = input()
        adjacency = list()

        for c in cube:
            for i, l in enumerate(name):
                if c == l and i not in adjacency:
                    adjacency.append(i)

        graph.append(adjacency)

    mt = [-1 for _ in range(m)]

    for v in range(n):
        used = [False for _ in range(n)]
        kuhn(v)

    ans = list()

    for j in mt:
        if j != -1:
            ans.append(j + 1)

    if len(ans) != m:
        print("NO")
    else:
        print("YES")
        for a in ans:
            print(a, end=" ")


if __name__ == '__main__':
    main()