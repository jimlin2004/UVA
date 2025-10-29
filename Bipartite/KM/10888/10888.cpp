#include <bits/stdc++.h>
using namespace std;

/*
    用BFS算出每個箱子到終點的距離
    然後跑最小權重KM即可
*/

#define maxn 45

int m, n;
char G[maxn][maxn];
vector<pair<int, int>> boxes;
vector<pair<int, int>> targets;

// 一個點到所有點的最短路
int dis[maxn][maxn];
int vis[maxn][maxn];
int dir[4][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};

// KM用
int W[maxn][maxn];
bool S[maxn], T[maxn];
int Lx[maxn];
int Ly[maxn];
int P[maxn]; // 配給誰

inline bool isValid(int i, int j)
{
    return (i > 0) && (i <= m) && (j > 0) && (j <= n);
} 

void bfs(int si, int sj)
{
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x3f, sizeof(dis));

    dis[si][sj] = 0;
    queue<pair<int, int>> q;
    q.push({si, sj});
    vis[si][sj] = true;

    while (!q.empty())
    {
        pair<int, int> curr = q.front();
        q.pop();

        for (int d = 0; d < 4; ++d)
        {
            int newI = curr.first + dir[d][0];
            int newJ = curr.second + dir[d][1];
            if (isValid(newI, newJ) && !vis[newI][newJ] && G[newI][newJ] != '#')
            {
                dis[newI][newJ] = dis[curr.first][curr.second] + 1;
                vis[newI][newJ] = true;
                q.push({newI, newJ});
            }
        }
    }
}

bool match(int i)
{
    S[i] = true;
    for (int j = 0; j < targets.size(); ++j)
    {
        if (Lx[i] + Ly[j] == W[i][j] && !T[j])
        {
            T[j] = true;
            if ((P[j] == -1) || match(P[j]))
            {
                P[j] = i;
                return true;
            }
        }
    }

    return false;
}

void update()
{
    // 找到最小diff
    int diff = 0x3f3f3f3f;
    for (int i = 0; i < boxes.size(); ++i)
    {
        if (S[i])
        {
            for (int j = 0; j < targets.size(); ++j)
            {
                if (!T[j])
                {
                    diff = min(diff, Lx[i] + Ly[j] - W[i][j]);
                }
            }
        }
    }

    for (int i = 0; i < boxes.size(); ++i)
    {
        if (S[i])
            Lx[i] -= diff;
        if (T[i])
            Ly[i] += diff;
    }
}

int KM()
{
    for (int i = 0; i < boxes.size(); ++i)
    {
        P[i] = -1;
        Lx[i] = Ly[i] = 0;

        for (int j = 0; j < targets.size(); ++j)
        {
            Lx[i] = max(Lx[i], W[i][j]);
        }
    }

    for (int i = 0; i < boxes.size(); ++i)
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
    for (int j = 0; j < targets.size(); ++j)
    {
        if (P[j] != -1)
        {
            res += W[P[j]][j];
        }
    }

    return res;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        scanf("%d %d",&m, &n);

        boxes.clear();
        targets.clear();

        for (int i = 1; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                scanf(" %c", &G[i][j]);
                if (G[i][j] == 'B')
                {
                    boxes.emplace_back(i, j);
                }
                else if (G[i][j] == 'X')
                {
                    targets.emplace_back(i, j);
                }
            }
        }

        for (int i = 0; i < boxes.size(); ++i)
        {
            // 計算boxes出發到所有終點的距離
            bfs(boxes[i].first, boxes[i].second);

            for (int j = 0; j < targets.size(); ++j)
            {
                W[i][j] = -dis[targets[j].first][targets[j].second];
            }
        }

        printf("%d\n", -KM());
    }

    return 0;
}

/*
2
5 8
BBBB....
.###...X
.XX#...X
...#....
........
5 8
BBBB....
.###...X
.XX#...X
...#....
........
*/