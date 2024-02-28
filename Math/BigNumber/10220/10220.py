# 直接python車過去，純考大數

def digitSum(n):
    res = 0
    while (n != 0):
        res += n % 10
        n //= 10
    return res

fact = [1]
for i in range(1, 1005):
    fact.append(fact[i - 1] * i)

while (1):
    try:
        print(digitSum(fact[int(input())]))
    except EOFError:
        break