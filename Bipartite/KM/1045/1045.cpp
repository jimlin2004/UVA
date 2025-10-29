#include <bits/stdc++.h>
using namespace std;

/*
    解題方式
    KM + 枚舉
    首先枚舉所有牆的建法 (橫牆 + 豎牆 + 對角線)

    然後每個石頭與牆的每個位置建邊
    邊上的權重就是石頭移動過去的距離(曼哈頓)
    如此每個位置配一顆石頭，所以是二分圖
    然後作KM求最小權重匹配 (將權重取負號就能求最小權)
*/


#define maxn 20

int stoneX[maxn];
int stoneY[maxn];

// KM用
int W[maxn][maxn];
int Lx[maxn];
int Ly[maxn];
bool S[maxn], T[maxn];
int L[maxn];
int n;


bool match(int i)
{
    S[i] = true;
    for (int j = 0; j < n; ++j)
    {
        if (Lx[i] + Ly[j] == W[i][j] && !T[j])
        {
            T[j] = true;
            if ((L[j] == -1) || match(L[j]))
            {
                L[j] = i;
                return true;
            }
        }
    }
    return false;
}

// 修改二分圖上的交錯路徑上點的權重
// 此舉是在通過調整vertex labeling看看能不能產生出新的增廣路(KM的增廣路要求Lx[i] + Ly[j] == W[i][j])
// 在這裡優先從最小的diff調調看，才能保證最大權重匹配
void update()
{
    int diff = 0x3f3f3f3f;

    for (int i = 0; i < n; ++i)
    {
        if (S[i])
        {
            for (int j = 0; j < n; ++j)
            {
                if (!T[j])
                    diff = min(diff, Lx[i] + Ly[j] - W[i][j]);
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        if (S[i]) Lx[i] -= diff;
        if (T[i]) Ly[i] += diff;
    }
}

int KM()
{
    for (int i = 0; i < n; ++i)
    {
        L[i] = -1;
        Lx[i] = Ly[i] = 0;

        for (int j = 0; j < n; ++j)
            Lx[i] = max(Lx[i], W[i][j]);
    }

    for (int i = 0; i < n; ++i)
    {
        while(1)
        {
            memset(S, false, sizeof(S));
            memset(T, false, sizeof(T));

            if (match(i))
                break;
            else
                update(); //去調整vertex labeling以增加增廣路徑
        }
    }

    int res = 0;

    for (int j = 0; j < n; ++j)
    {
        if (L[j] != -1)
            res += W[L[j]][j];
    }

    return res;
}


inline int getDis(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

int main()
{
    int testcase = 0;

    while (scanf("%d", &n) && n)
    {
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d", &stoneX[i], &stoneY[i]);
            // 變成0-based index
            --stoneX[i];
            --stoneY[i];
        }

        int res = -0x3f3f3f3f;
        // 枚舉橫牆
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                for (int u = 0; u < n; ++u)
                {
                    // 負號 for 最小權重
                    W[u][j] = -getDis(stoneX[u], stoneY[u], j, i);
                }
            }

            res = max(res, KM());
        }

        // 枚舉豎牆
        for (int j = 0; j < n; ++j)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int u = 0; u < n; ++u)
                {
                    W[u][i] = -getDis(stoneX[u], stoneY[u], j, i);
                }
            }

            res = max(res, KM());
        }

        // 計算主對角線
        for (int i = 0; i < n; ++i)
        {
            for (int u = 0; u < n; ++u)
            {
                W[u][i] = -getDis(stoneX[u], stoneY[u], i, i);
            }
        }

        res = max(res, KM());

        // 計算另一個對角線
        for (int i = 0; i < n; ++i)
        {
            for (int u = 0; u < n; ++u)
            {
                W[u][i] = -getDis(stoneX[u], stoneY[u], n - i - 1, i);
            }
        }

        res = max(res, KM());

        printf("Board %d: %d moves required.\n\n", ++testcase, -res);
    }

    return 0;
}