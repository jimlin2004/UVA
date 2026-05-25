#include <bits/stdc++.h>
using namespace std;

/*
    下方是這題神奇的AI提供
    機率論O(N^2)解法 (我也看不懂)
    1. 收集娃娃問題
    扭蛋機裡有K種我們想要的隱藏款娃娃（對應K個我們還沒去過的連通塊。
    抽中第i種娃娃的機率是 $\frac{S_i}{N-1}$。
    抽中已經有的娃娃（跳到已經去過的點）就浪費一次機會。
    請問「集齊所有隱藏款」的期望次數是多少？

    2. Min-Max 恆等式 (排容原理)
    在機率論中，要求「全部事件都發生的期望時間 $E[\max(T)]$」，可以用各個子集「最先發生事件的期望時間 $E[\min(T)]$」來做排容：
    $$E[\max(T_1, T_2, \dots, T_k)] = \sum_i E[T_i] - \sum_{i<j} E[\min(T_i, T_j)] + \sum_{i<j<k} E[\min(T_i, T_j, T_k)] - \dots$$
    翻譯成白話文：
    我們選定一個連通塊的子集 $C$。
    要「隨機亂跳直到第一次踩中 $C$ 裡面任何一個點」的期望步數是多少？
    因為踩中 $C$ 的機率是 $\frac{\sum_{c \in C} S_c}{N-1}$，所以期望步數就是它的倒數：$$E[\min(C)] = \frac{N-1}{\sum_{c \in C} S_c}$$把這個代入排容原理，
    我們要求的總期望步數 $E$ 就是：$$E = \sum_{C \neq \emptyset} (-1)^{|C|-1} \frac{N-1}{\sum_{c \in C} S_c}$$
    (註：這條公式展開後有 $2^K$ 項，其實就是你狀壓 DP 窮舉的所有狀態！)

    3. 從 $O(2^K)$ 降維到 $O(N^2)$：背包 DP 技巧
    既然公式裡的分母只有「子集的總大小（節點數）」，
    而總節點數最大也才 $N$。我們根本不需要窮舉 $2^K$ 種組合，
    我們只需要知道：「總大小為 $S$ 的子集中，正負號抵銷後剩下多少係數？」
    我們可以建構一個多項式：$$P(x) = \prod_{i=1}^K (1 - x^{S_i})$$
    為什麼是這樣？
    對於每一個連通塊 $i$，我們可以選擇「不選它 (對應 $1$)」或「選它並帶有負號 (對應 $-x^{S_i}$)」。
    如果你把這個多項式乘開，
    $x^S$ 的係數剛好就會是：「所有大小總和為 $S$ 的子集，其 $(-1)^{|C|}$ 的總和」！因為我們要的是 $(-1)^{|C|-1}$，所以係數加個負號就好了。
*/

int parent[35];

int findRoot(int x)
{
    if (parent[x] < 0)
        return x;
    return parent[x] = findRoot(parent[x]);
}

bool uni(int x, int y)
{
    int r1 = findRoot(x);
    int r2 = findRoot(y);
    if (r1 == r2)
        return false;
    if (parent[r1] < parent[r2])
    {
        parent[r1] += parent[r2];
        parent[r2] = r1;
    }
    else
    {
        parent[r2] += parent[r1];
        parent[r1] = r2;
    }
    return true;
}


int main()
{
    int T;
    scanf("%d", &T);
    int testcase = 0;

    while (T--)
    {
        int n, m;
        scanf("%d %d", &n, &m);

        memset(parent, -1, sizeof(parent));

        // 輸入edge並且處理DSU
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            uni(u, v);
        }

        // 收集所有不是起點所在的連通塊大小
        vector<int> targets;
        int startRoot = findRoot(1); // 起點1的root
        for (int i = 1; i <= n; ++i)
        {
            // 如果這個點是root，且不是起點1個連通塊
            if (findRoot(i) == i && i != startRoot)
                targets.push_back(-parent[i]); // 這裡用-parent[i]是因為我用的DSU優化
        }

        // 計算排容係數 (01 背包 DP 模擬多項式乘法)
        // 目標是展開多項式： P(x) = ∏(1 - x^(sz_i))
        // dp[j] 的意義：在所有大小總和剛好為 j 的組合中，其排容符號 (-1)^|C| 的總和
        vector<int> dp(n + 5, 0);
        dp[0] = 1; // 空集合的大小為 0，挑選了 0 個連通塊，(-1)^0 = 1

        for (int sz : targets) 
        {
            // 0/1 背包必須「由大到小」轉移，確保每個連通塊 sz 在這次迴圈只被使用一次
            for (int j = n; j >= sz; --j) {
                // dp[j] (不選 sz 的係數和) 加上 (-dp[j-s]) (選了 sz，所以多乘一個負號)
                dp[j] = dp[j] - dp[j - sz];
            }
        }

        // 結合 Min-Max 恆等式結算期望值
        // 公式：總期望值 E = sum { (-1)^(|C|-1) * (N-1) / 總大小 }
        // 也就是：E = sum { -dp[j] * (N-1) / j }
        double ans = 0.0;
        for (int j = 1; j <= n; ++j)
        {
            if (dp[j] != 0) 
            { 
                // 如果存在大小總和為 j 的組合
                // 踩中總大小為 j 的目標子集的期望步數是 (n-1)/j
                // 乘上排容係數 -dp[j] (因為公式要是 (-1)^(|C|-1)，所以對 dp[j] 取負號)
                ans += (double)(-dp[j]) * (n - 1) / j;
            }
        }

        printf("Case %d: %.6lf\n", ++testcase, ans);
    }
}