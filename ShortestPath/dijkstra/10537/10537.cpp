#include <bits/stdc++.h>
using namespace std;

/*
    這題要反推抽稅前的數值
    如果是village直接+1
    如果是town則要計算
    抽稅後 N = M - 下高斯[M / 20]
    -> M = 上高斯[19 N / 20]
    其中M是抽稅後的值

    所以Dijkstra反過來從t開始搜
    一路回推找答案
    過程要維護字典序
*/

#define maxn 256

vector<vector<char>> G;
long long dis[maxn]; // 終點到所有節點的cost
char parent[maxn];

struct Item
{
    char u;
    long long w;
    bool operator < (const Item& other) const
    {
        return w > other.w;
    }
};

long long calW(char v, long long w)
{
    if ('A' <= v && v <= 'Z')
        return (long long)ceil(w * 20 / 19.0);
    return w + 1;
}

void dijkstra(char s, char t, long long p)
{
    memset(dis, 0x3f, sizeof(dis));

    priority_queue<Item> pq;
    dis[s] = p;
    pq.push({s, dis[s]});
    parent[s] = -1;

    while (!pq.empty())
    {
        Item curr = pq.top();
        pq.pop();

        long long newW = calW(curr.u, dis[curr.u]);
        
        for (char v: G[curr.u])
        {
            

            if (dis[v] > newW)
            {
                dis[v] = newW;
                parent[v] = curr.u;
                pq.push({v, dis[v]});
            }
            else if (dis[v] == newW && parent[v] > curr.u)
            {
                parent[v] = curr.u;
                pq.push({v, dis[v]});
            }
        }
    }
}

int main()
{
    int tc = 0;

    int n;
    while (scanf("%d", &n) && n != -1)
    {

        getchar();

        G.assign(maxn, {});

        char u, v;
        for (int i = 0; i <  n; ++i)
        {
            scanf("%c %c", &u, &v);
            getchar();
            G[u].push_back(v);
            G[v].push_back(u);
        }

        long long p;
        char s, t;
        scanf("%lld %c %c", &p, &s, &t);
        getchar();

        dijkstra(t, s, p);

        printf("Case %d:\n", ++tc);
        printf("%lld\n", dis[s]);
        
        int curr = s;
        while (parent[curr] != -1)
        {
            printf("%c-", curr);
            curr = parent[curr];
        }
        printf("%c\n", curr);
    }

    return 0;
}

/*
1
a Z
19 a Z
5
A D
D X
A b
b c
c X
39 A X
5
A D
D X
A b
b c
c X
10 A X
-1


0
2 A A
25
A B
B C
C D
D E
E F
F G
G H
H I
I J
J K
K L
L M
M N
N O
O P
P Q
Q R
R S
S T
T U
U V
V W
W X
X Y
Y Z
999999999 A Z
4
A b
A B
b c
B c
18 A c
4
A b
A B
b c
B c
19 A c
5
A D
D X
A b
b c
c X
39 A X
-1
*/