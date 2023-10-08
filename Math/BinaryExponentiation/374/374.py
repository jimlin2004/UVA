def p(B, P, M):
    if (P == 0):
        return 1 % M
    if (P == 1):
        return B
    res = p(B, P // 2, M) % M
    res = (res % M) * (res % M)
    res %= M
    if (P % 2 == 1):
        res *= B % M
        res %= M
    return res

while (1):
    try:
        B = int(input())
        P = int(input())
        M = int(input())
        print(p(B % M, P, M))
        input()
    except EOFError:
        break