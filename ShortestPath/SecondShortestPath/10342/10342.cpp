#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

/*
    概念:
        求次短路，但可以有回去繞圈圈，利用dijkstra去修改
        一邊求最短路也一邊維護次短路

        同時因為可以回去繞圈，所以priority_queue中的Node(Item)裡的w並不是一般
        的s到u點當前的cost，而是一直繞圈(可能沒繞圈)累積出來的路徑長(total cost)

        由於要繞圈，visited陣列就不需要了

        注意最短路與次短路不能一樣長

    Note: 在想priority_queue的必要性，是否如spfa一樣用queue即可?

    2024/03/07更新: 不用priority_queue, 用queue就行了(速度更快，pq要O(logn)維護heap)
                    基本上從dijkstra變成用SPFA的思維
*/

#define maxn 105

struct Edge
{
    int u, v, w;
};

struct Item
{
    //w並不是一般的s到u點當前的cost，而是一直繞圈(可能沒繞圈)累積出來的路徑長
    int u, w;
    bool operator < (const Item& other) const
    {
        return this->w > other.w;
    }
};

vector<vector<Edge>> G;

//dis[u][v][0] -> u到v的最短路
//dis[u][v][1] -> u到v的次短路
int dis[maxn][maxn][2];

void dijkstra(int s)
{
    queue<Item> q;
    // priority_queue<Item> pq;
    q.push({s, 0});
    while (!q.empty())
    {
        Item curr = q.front();
        q.pop();

        //如果s到u的最短路還沒出現過，就紀錄第一次遇到的路徑長
        if (dis[s][curr.u][0] == 0x3f3f3f3f)
        {
            dis[s][curr.u][0] = curr.w;
        }
        else
        {
            //後面繞圈(可能沒繞圈)到了u可否鬆弛
            if (dis[s][curr.u][0] > curr.w)
            {
                //最短路變短了，次短路就變成之前的最短路
                dis[s][curr.u][1] = dis[s][curr.u][0];
                dis[s][curr.u][0] = curr.w;
            }
            //最短路不變，且防止次短路與最短路變一樣而設置
            else if (dis[s][curr.u][0] == curr.w)
                continue;
            //做到這邊時，不可能是更短的最短路
            //所以判斷可否鬆弛次短路
            else if (dis[s][curr.u][1] > curr.w)
            {
                dis[s][curr.u][1] = curr.w;
            }
            //到了這邊代表比最短路長，也比次短路長，
            //那就不用再將u的鄰接點去試試看有沒有更好的答案
            //因為不會比目前已知的更好
            else
                continue;
        }

        //把鄰接點都放進去pq看有沒有更好的答案
        for (const Edge& edge: G[curr.u])
        {
            q.push({edge.v, curr.w + edge.w});
        }
    }
}

int main()
{
    int Case = 0;
    int n, r;
    while (scanf("%d %d", &n, &r) != EOF)
    {
        G.assign(n + 5, vector<Edge>());
        memset(dis, 0x3f, sizeof(dis));

        int u, v, w;
        for (int i = 0; i < r; ++i)
        {
            scanf("%d %d %d", &u, &v, &w);
            G[u].push_back({u, v, w});
            G[v].push_back({v, u, w});
        }

        //直接用dijkstr去求每一點到每一點之間的最短路與次短路
        for (int i = 0; i < n; ++i)
        {
            dijkstra(i);
        }

        int q;
        scanf("%d", &q);
        printf("Set #%d\n", ++Case);
        while (q--)
        {
            scanf("%d %d", &u, &v);
            
            //不存在次短路
            //或點不連接，就會是0x3f3f3f3f(無限大)
            if (dis[u][v][1] == 0x3f3f3f3f)
                puts("?");
            else
                printf("%d\n", dis[u][v][1]);
        }
    }
    return 0;
}

/*
4 3
0 1 12
0 2 20
1 2 15
3
0 1
0 2
0 3

4 3
0 1 11
0 2 20
1 2 15
3
0 1
0 2
0 3
*/