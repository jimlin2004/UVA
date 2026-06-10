#include <bits/stdc++.h>
using namespace std;

/*
    題意很簡單
    就是檢查在子序列中有沒有三個數字可能成為等差序列
    做法看下方O(n^2)
*/

// 原序列
int A[10005];
// 用來標記每個數字最後出現在哪個index(最右邊)
int B[10005];

bool check(int n)
{
    // 枚舉第一個數字
    for (int i = 0; i < n; ++i)
    {
        // 枚舉第二個數字
        for (int j = i + 1; j < n; ++j)
        {
            // 利用等差的公差算出第三個數字
            int k = A[j] - A[i] + A[j];
            if (k < 0 || k >= n) // 超出範圍的都不可能
                continue;
            if (B[k] > j) // 如果第三個數字比第二個數字更右邊，就有答案了
                return true;
        }
    }

    return false;
}

int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        getchar();

        // 一邊輸入一邊維護B的值是最右邊的那一個
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &A[i]);
            B[A[i]] = i;
        }

        puts((check(n)) ? "no" : "yes");
    }

    return 0;
}