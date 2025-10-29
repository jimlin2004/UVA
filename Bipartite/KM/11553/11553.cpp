#include <bits/stdc++.h>
using namespace std;

/*
KM靶題
將row與col做二分圖
然後跑最小權重的KM
權重取負，答案也要取負回來
*/

#define maxn 20

int A[maxn][maxn];
int W[maxn][maxn]; // 第 i row對第 j col
bool S[maxn];
bool T[maxn];
int Lx[maxn];
int Ly[maxn];
int L[maxn];
int n;

bool match(int u)
{
    S[u] = true;
    for (int v = 0; v < n; ++v)
    {
        if (Lx[u] + Ly[v] == W[u][v] && !T[v])
        {
            T[v] = true;
            if ((L[v] == -1) || match(L[v]))
            {
                L[v] = u;
                return true;
            }
        }
    }

    return false;
}

void update()
{
    int diff = 0x3f3f3f3f;
    for (int u = 0; u < n; ++u)
    {
        if (S[u])
        {
            for (int v = 0; v < n; ++v)
            {
                if (!T[v])
                    diff = min(diff, Lx[u] + Ly[v] - W[u][v]);
            }
        }
    }

    for (int u = 0; u < n; ++u)
    {
        if (S[u])
            Lx[u] -= diff;
        if (T[u])
            Ly[u] += diff;
    }
}

int KM()
{
    for (int i = 0; i < n; ++i)
    {
        L[i] = -1;
        Lx[i] = Ly[i] = 0;

        // 找最大的
        for (int j = 0; j < n; ++j)
            Lx[i] = max(Lx[i], W[i][j]);
    }

    for (int i = 0; i < n; ++i)
    {
        while (1)
        {
            memset(S, 0, sizeof(S));
            memset(T, 0, sizeof(T));

            if (match(i))
                break;
            else
                update();
        }
    }

    int res = 0;
    for (int v = 0; v < n; ++v)
    {
        if (L[v] != -1)
            res += W[L[v]][v];
    }

    return res;
}


int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                scanf("%d", &A[i][j]);
            }
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                W[i][j] = -A[i][j];
            }
        }

        printf("%d\n", -KM());
    }

    return 0;
}

/*
3
2
10 10
-5 -5
2
10 -5
10 -5
2
10 -5
-5 10
*/