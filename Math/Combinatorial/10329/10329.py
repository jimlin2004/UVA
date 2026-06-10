import math

"""

問分數的分子 / 分母 (都是C^n_r) 答案是多少

直接python暴力

"""

def C(n, r):
    return math.factorial(n) // math.factorial(n - r) // math.factorial(r)

while (1):
    try:
        n, m = list(map(int, input().split()))

        p = 1
        q = 1

        for i in range(n):
            x, y = list(map(int, input().split()))
            p *= C(x, y)
        
        for i in range(m):
            x, y = list(map(int, input().split()))
            q *= C(x, y)
        
        if (p % q == 0):
            res = p // q
            if (math.log10(res) >= 100):
                print(-1)
            else:
                print(res)
        else:
            print(0)

    except EOFError:
        break