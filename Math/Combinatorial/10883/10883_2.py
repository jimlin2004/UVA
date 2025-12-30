import math

# 下方不知道為什麼UVA會runtime error

fact = [0, math.log(1), math.log(2)]

for i in range(3, 50005):
    fact.append(fact[-1] + math.log(i))

def comb(n, r):
    return fact[n] - fact[r] - fact[n - r]


T = int(input())

testcase = 0

for t in range(T):
    n = int(input())
    A = list(map(float, input().split(" ")))
    
    res = 0

    for i in range(n):
        res += A[i] * math.exp(comb(n - 1, i) - (n - 1) * math.log(2))

    testcase += 1

    # print(f"Case #{testcase}: {res:.3f}") # UVA太舊了QQ
    print("Case #%d: %.3f" % (testcase, res))