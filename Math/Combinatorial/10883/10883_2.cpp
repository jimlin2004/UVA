#include <bits/stdc++.h>
using namespace std;


/*
    題目是兩兩數字一直取平均值到剩下一個

    事實上這個過程就像是巴斯卡三角形

    比如

    1      2       3       4       5
       1.5    2.5     3.5     4.5
           2       3       4
              2.5     3.5
                   3

    從上面的過程可以發現到我們可以去算出一開始的數字對於最終答案的權重是多少

    經過觀察發現就像是巴斯卡三角形的倒過來版本(掉彈珠，往左往右)
    所以對於n個數字
    最上面每個人的權重就是二項式定理
    [ C(4, 0) * 1 + C(4, 1) * 2 + C(4, 2) * 3 + C(4, 3) * 4 + C(4, 4) ] / (2 ^ (n - 1))

    由於題目的n = 50000很大，所以只能套log估算
    C(n, r)套log很簡單，由於每個數字都要 / (2 ^ (n - 1))
    套log發現 log(2^(n - 1)) = (n - 1) * log(2)
    所以等於每一項在計算時先都 - (n - 1) * log(2)

    最後套exp算回來即可
*/


double fact[50005]; // log 後的階層表
double A[50005];


double comb(int n, int r) // log 後的 C n 取 r
{
    return fact[n] - fact[r] - fact[n - r]; // log 相乘變相加
}

int main()
{
    fact[0] = 0;
    fact[1] = log(1);
    fact[2] = log(2);
    for (int i = 3; i < 50005; ++i)
        fact[i] = fact[i - 1] + log(i); // log相乘變相加
    
    int T;
    scanf("%d", &T);

    for (int testcase = 1; testcase <= T; ++testcase)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            scanf("%lf", &A[i]);
        }

        double res = 0;

        for (int i = 0; i < n; ++i)
        {
            res += A[i] * exp(comb(n - 1, i) - (n - 1) * log(2));
        }

        printf("Case #%d: %.3f\n", testcase, res);
    }


    return 0;
}