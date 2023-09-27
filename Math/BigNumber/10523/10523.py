while (1):
    try:
        N, A = list(map(int, input().split()))
        currentA = A
        res = 0
        for i in range(1, N + 1):
            res += i * currentA
            currentA *= A
        print(res)
    except EOFError:
        break