#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

#define maxn 105

/*
    bfs會超時
    改用spfa去找最長路
*/

vector<vector<int>> G;
int maxLen, finishP;
bool inqueue[maxn];
int dis[maxn];

void spfa(int s)
{
    maxLen = -1;
    finishP = 0x3f3f3f3f;
    memset(dis, 0, sizeof(dis));
    memset(inqueue, 0, sizeof(inqueue));
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    inqueue[s] = true;
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        inqueue[curr] = false;
        if (dis[curr] == maxLen)
        {
            if (curr < finishP)
                finishP = curr;
        }
        if (dis[curr] > maxLen)
        {
            maxLen = dis[curr];
            finishP = curr;
        }

        for (int v: G[curr])
        {
            if (dis[v] < dis[curr] + 1)
            {
                dis[v] = dis[curr] + 1;
                if (!inqueue[v])
                    q.push(v);
            }
        }
    }
}

int main()
{
    int Case = 0;
    int n;
    while (scanf("%d", &n) && n)
    {
        G.assign(n + 5, vector<int>());

        int s;
        scanf("%d", &s);
        int u, v;
        while (scanf("%d %d", &u, &v) && (u != 0 && v != 0))
            G[u].emplace_back(v);
        
        spfa(s);

        printf("Case %d: The longest path from %d has length %d, finishing at %d.\n\n", ++Case, s, maxLen, finishP);
    }
    return 0;
}