"""
    題意很簡單: 問m^n個位數是多少
    但 0 <= m, n <= 10^101

    解法:
    因為只問個位數，所以其實是在解 m^n mod 10

    然後雖然n很大，但因為是mod的問題
    直接快速冪爆開算答案即可(python的pow可以直接處理mod)
"""

while (1):
    m, n = list(map(int, input().split(" ")))
    m %= 10

    if (m == 0 and n == 0):
        break

    print(pow(m, n, mod=10))