# 大數 + 二分搜

import sys

# 找第一個大於等於的(左閉右開)
def bs1(target, fib):
    l = 0
    r = len(fib)
    while(l < r):
        mid = (l + r) // 2
        if (fib[mid] >= target):
            r = mid
        else:
            l = mid + 1
    return l

# 找最後一個小於等於的(左閉右開)
def bs2(target, fib):
    l = 0
    r = len(fib)
    while(l < r):
        mid = (l + r) // 2
        if (fib[mid] <= target):
            l = mid + 1
        else:
            r = mid
    return r - 1

def main():
    maxFib = 10 ** 100 + 5
    fib = [0, 1, 1]

    while(fib[-1] <= maxFib):
        fib.append(fib[-1] + fib[-2])

    for line in sys.stdin:
        a, b = map(int, line.split(" "))
        if (a == 0 and b == 0):
            break
        aIndex = bs1(a, fib)
        bIndex = bs2(b, fib)
        # 特判 因為1的有兩個
        # 然後在這題0不算在fib中，所以視為第2個1
        if (a == 0):
            aIndex = 2
        if (a == 1):
            aIndex = 2
        if (b == 1):
            bIndex = 2
        print(bIndex - aIndex + 1)

main()