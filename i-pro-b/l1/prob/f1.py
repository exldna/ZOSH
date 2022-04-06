n: int
m: int

graph: list
used: list
match: list


def kuhn(v):

    global graph, used, match

    if (used[v]):
        return False;

    used[v] = True;

    for vt in graph[v]:
        if match[vt] == -1 or kuhn(match[vt]):
            match[vt] = v
            return True
    
    return False


def main():

    global n, m
    global graph, used, match

    n, m = map(int, input().split())

    graph = [list() for _ in range(n)]
    match = [-1 for _ in range(n)]

    for _ in range(m):
        x, y = map(int, input().split())
        graph[x - 1].append(y - 1)

    for v in range(n):
        used = [False for _ in range(n)]
        kuhn(v)

    print(n - len(match) + match.count(-1))


if __name__ == '__main__':
    main()
