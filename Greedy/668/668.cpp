#include <bits/stdc++.h>
using namespace std;

/*
    題意:
    要用不重複的數字，和為n，使乘積最大

    貪婪:
    1. 在乘法中1沒有任何貢獻，所以使用1只會讓後續乘積變小
       所以拆分數字從2開始就好了
    2. 總和固定的情況下，把數字拆成越多大於2的數字，最後乘積會比少數幾個大數字相乘還要大
       比如 9 可以拆成 9 < (4, 5) [4 x 5 = 20] < (2, 3, 4) [2 x 3 x 4 = 24]
    3. 算幾不等式說明: 數字彼此越靠近，乘積會越大

    作法:
    直接從2、3、4...k開始填數字，然後剩下餘數diff
    然後由於算幾不等式的說明，好的分法就是把diff平均分配給每個數字，而不是加到單一數字上
    然後為了避免造成數字重複，需要先從最大數字開始往回加1
    同時一個個加可以使數字盡量連續
*/

int res[1005];
int m;


int main()
{
    int T;
    scanf("%d", &T);

    bool first = true;

    while (T--)
    {
        if (first)
            first = false;
        else
            puts("");

        m = 0;

        int n;
        scanf("%d", &n);

        // 直接2、3、4...一路填數字
        int sum = 0;
        for (int i = 2; i <= n; ++i)
        {
            if (sum + i > n)
                break;
            res[m++] = i;
            sum += i;
        }

        // 看剩下多少餘數
        int diff = n - sum;
        int j = m - 1;
        // 開始一個個往回加1
        while (diff)
        {
            ++res[j];
            --diff;

            // 數字可能個數不夠分完diff，
            // 所以可能要不斷循環加1
            j = (j - 1 + m) % m;
        }

        printf("%d", res[0]);
        for (int i = 1; i < m; ++i)
            printf(" %d", res[i]);
        puts("");
    }
}