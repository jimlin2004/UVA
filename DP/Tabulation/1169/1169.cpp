#include <bits/stdc++.h>
using namespace std;


/*
    題目要求要照順序撿
    定義dp[i] -> 將前i個貨物撿完的最少移動量(會回到原點)
    轉移式:
        找到第 j 個點，使得撿到j回到原點後再一路撿 j + 1 ~ i 的貨物能夠有最少的移動量
        所以公式為
        dp[i] = min{
            dp[j]           // 撿到j的最少移動量，且會回到原點，包含回到原點的距離
            + d2o[j + 1]    // 從原點走到 j + 1 的移動量
            + dis(j + 1, i) // 從 j + 1 ~ i 的移動量
            + d2o[i]        // 走回原點
        } where j <= i, sumW(j + 1 ~ i) <= C
    注意: 找j的過程需要用單調隊列優化(看下方)
*/


#define maxn 100005

struct Point
{
    int x, y;
};

Point points[maxn];
int d2o[maxn]; // 點到原點的距離
int prefixDis[maxn];
int prefixWeight[maxn];
int dp[maxn];

// 曼哈頓距離
inline int getDis(const Point& u, const Point& v)
{
    return abs(v.x - u.x) + abs(v.y - u.y);
}

// 為了方便將dp轉移式中與j有關的寫成函式管理
inline int f(int j)
{
    return dp[j] - prefixDis[j + 1] + d2o[j + 1];
}

int main()
{
    // 放原點為第0點
    points[0] = {0, 0};
    prefixDis[0] = 0;
    prefixWeight[0] = 0;

    bool first = true;

    int T;
    scanf("%d", &T);
    while (T--)
    {
        int C, n;
        scanf("%d %d", &C, &n);

        int w;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d %d %d", &points[i].x, &points[i].y, &w);
            d2o[i] = getDis(points[i], points[0]);
            prefixDis[i] = prefixDis[i - 1] + getDis(points[i - 1], points[i]);
            prefixWeight[i] = prefixWeight[i - 1] + w;
        }

        deque<int> dq;
        dq.push_back(0);

        for (int i = 1; i <= n; ++i)
        {
            // 因為w都是正的，所以當目前w累積起來大於C後，就不用討論dq裡的front
            while (!dq.empty() && (prefixWeight[i] - prefixWeight[dq.front()] > C))
                dq.pop_front();
            
            dp[i] = f(dq.front()) + prefixDis[i] + d2o[i];

            // 如果 dq 的 back 的 f() 比 i 的 f() 大，那就不用保留了，因為 i 的 f() 更好
            while (!dq.empty() && (i <= n) && (f(dq.back()) >= f(i)))
                dq.pop_back();
            
            dq.push_back(i);
        }

        if (first)
            first = false;
        else
            puts("");
        
        printf("%d\n", dp[n]);
    }

    return 0;
}