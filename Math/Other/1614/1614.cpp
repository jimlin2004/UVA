#include <bits/stdc++.h>
using namespace std;

/*
    老師解法
    首先所有數字總和一定要是偶數
    否則沒答案
    因為要相消，所以只需要找一種解法能加出currS = 總和 / 2

    題目的 1 <= a[i] <= i是重要的條件
    需要用數學歸納法推出定理1: 推導1.png
    推導1.png在解法2也有證明
    然後利用定理1可以推出定理2: 推導2.png
    定理2告訴我們一種解法可以找到組成的方式
    S[k] <= currS <= S[k + 1]
    此時代表currS是由a_{k + 1}加總起來的(這句話指的是其中一種特定組法)
    所以將currS - a_{k + 1}後繼續一樣的方式檢查
    就能找到一種組法
    注意這題答案肯定不唯一(b可以1的與-1的互換)
*/

#define maxn 100005

long long a[maxn];
long long prefix[maxn];
int b[maxn];

int main()
{
    int n;
    prefix[0] = 0;
    while (scanf("%d", &n) != EOF)
    {    
        for (int i = 1; i <= n; ++i)
        {
            scanf("%lld", &a[i]);
            prefix[i] = prefix[i - 1] + a[i];
        }
        long long S = prefix[n];
        if (S % 2 != 0)
        {
            puts("No");
            continue;
        }
        S /= 2;
        for (int i = n; i >= 1; --i)
        {
            if (prefix[i] >= S && S > prefix[i - 1])
            {
                S -= a[i];
                b[i] = 1;
            }
            else
                b[i] = -1;
        }

        puts("Yes");
        printf("%d", b[1]);
        for (int i = 2; i <= n; ++i)
            printf(" %d", b[i]);
        puts("");
    }
    return 0;
}