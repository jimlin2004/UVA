#include <bits/stdc++.h>
using namespace std;

/*
題意:
    給定N，代表質數的個數
    問用N個質數成起來是哪個階乘
    例如
    N = 4
    2 x 2 x 2 x 3 = 24 = 4!
    因為質因數分解是唯一的
    所以直覺想到建表

    需要一點時間優化，細節看下方
*/

// 因為 N <= 10000001，2700000!大概有1000萬個質因數個數
const long long maxP = 2800000;

long long prefix[maxP];

int main()
{
    /*
        先算出每個數字有多少質因數個數

        兩個數相乘的質因數個數，等於兩個數各自質因數個數相加

        用 Ω(n) 來表示數字n的質因數總數
        Ω(A x B) = Ω(A) + Ω(B)

        如果不用這個性質算
        而是先建質數表再暴力算每個數字的質因數個數會超時
        改用下方作法相法接近埃氏篩，複雜度O(N log log N)
    */
    fill(prefix, prefix + maxP, 1);
    prefix[0] = prefix[1] = 0; // 0 和 1都不是質數，手動設為0
    // 類似埃氏篩的概念
    for (long long i = 2; i < maxP; ++i)
    {
        // 如果這個數還是1，這個數就是質數
        if (prefix[i] == 1)
        {
            // i是質數，更新所有i的倍數(i x j)
            // 在這裡由小到大保證了最終正確性
            // 運算過程中會存在錯誤的值
            // 但是因為i的遞推，最後答案會是對的
            // 比如 18 = 2 x 3 x 3
            // 一開始算 prefix[18] = prefix[2] x prefix[9]的時候
            // 因為prefix[9]沒算，所以會是錯的
            // 但是後面在算prefix[18] = prefix[3] x prefix[6]的時候
            // 6個最大因數是3，所以prefix[6]已經被算完
            // 所以這時候prefix[18]就會是對的
            for (long long j = 2; i * j < maxP; ++j)
                prefix[i * j] = prefix[i] + prefix[j];
        }
    }

    /*
        因為prefix[i]是i個質因數個數
        那麼要轉成算i!的質因數個數
        其實就是用
        n! = n x (n - 1) x (n - 2) x ... x 1
        那質因數個數就是prefix的前綴和
        prefix[n] = prefix[n] + prefix[n - 1] + prefix[n - 2] + ... + prefix[1]
    */
    for (int i = 2; i < maxP; ++i)
    {
        prefix[i] = prefix[i - 1] + prefix[i];
    }

    int tc = 0;
    int n;
    while (scanf("%d", &n) && n >= 0)
    {
        // 因為前綴和是單調上升的
        // 所以用二分搜看答案有沒有在表中
        int target = lower_bound(prefix, prefix + maxP, n) - prefix;
        if (target < maxP && prefix[target] == n)
            printf("Case %d: %d!\n", ++tc, target);
        else
            printf("Case %d: Not possible.\n", ++tc);
    }

    return 0;
};