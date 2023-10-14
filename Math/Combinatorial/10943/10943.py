import math

#此題為離散數學 n用r個數字相加能表示的數量
#c(n + r - 1, r - 1) n個東西用r - 1個隔板隔開的組合數

while (1):
    n, r = map(int, input().split())
    if (n == 0 and r == 0):
        break
    print(math.comb(n + r - 1, r - 1) % 1000000)