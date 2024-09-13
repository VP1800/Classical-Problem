import decimal
from decimal import Decimal

### utility functions for fractions

def lowest_terms(x):
    a, b = x
    while (a & 1) == 0 and (b & 1) == 0:
        a >>= 1
        b >>= 1
    return (a, b)

def add(x, y):
    a, b = x
    c, d = y
    if b > d:
        a, c = c, a
        b, d = d, b
    # b <= d
    while b < d:
        a <<= 1
        b <<= 1
    p = a + c
    q = b
    return lowest_terms((p, q))

def average(x, y):
    p, q = add(x, y)  # already lowest terms
    if (p & 1) == 0:
        p >>= 1
    else:
        q <<= 1
    return (p, q)

def toposort(i, parents, result):
    if result[i] >= 0:
        return
    if len(parents[i]) > 0:
        toposort(parents[i][0], parents, result)
        toposort(parents[i][1], parents, result)
    result[i] = result[-1]
    result[-1] += 1

### compute the coefficient of relationship recursively

def calc(a, b, parents, topo, memo):
    if memo[a][b][0] != -1:
        return memo[a][b]
    if a == b:
        memo[a][b] = memo[b][a] = (1, 1)
        return (1, 1)
    if topo[a] < topo[b]:
        a, b = b, a
    if len(parents[a]) == 0:
        # if `a` is topologically later than `b`, but `a` has no parents, then
        # `b` can't be descended from `a` nor can they have a common ancestor
        memo[a][b] = memo[b][a] = (0, 1)
        return (0, 1)
    # `a` has parents
    memo[a][b] = memo[b][a] = average(
      calc(parents[a][0], b, parents, topo, memo),
      calc(parents[a][1], b, parents, topo, memo)
    )
    return memo[a][b]

### main program

t = int(input())
while t > 0:
    t -= 1
    n, k = input().split()
    n = int(n)
    k = int(k)
    parents = [() for _ in range(n)]
    while k > 0:
        k -= 1
        a, b, c = input().split()
        a = int(a) - 1
        b = int(b) - 1
        c = int(c) - 1
        parents[a] = (b, c)

    # simple toposort
    topo = [-1 for _ in range(n + 1)]
    topo[-1] = 0
    for i in range(n):
        toposort(i, parents, topo)

    m = int(input())
    memo = [[(-1, 0) for _ in range(n)] for _ in range(n)]
    decimal.getcontext().prec = 300
    while m > 0:
        m -= 1
        a, b = input().split()
        a = int(a) - 1
        b = int(b) - 1
        result = calc(a, b, parents, topo, memo)
        d = Decimal(result[0]) / Decimal(result[1]) * 100
        print("{:,f}%".format(d.normalize()))