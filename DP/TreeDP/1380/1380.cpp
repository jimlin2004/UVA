#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;


/*
    難題
    解法
    1. 先忽略undirected edge，用dfs得到最長有向路徑的邊數 maxUndirLen
    2. 判斷是否可以透過調成undirected edge的方向使得最長路徑邊數不超過 maxUndirLen
        如果可以 -> 答案是maxUndirLen + 1
        不能 -> 答案是maxUndirLen + 2
*/


#define maxn 205


struct Edge
{
    // dir == 0 undirected, dir == 1 forward, dir == 2 backward
    int u, v, dir;
};

struct UndirectedEdgeItem
{
    int v; // 指向哪個節點
    int f;
    int b;
};


vector<vector<Edge>> G;
int n; // 有多少節點
int root; // 樹的root 
int maxUndirLen; // 在不考慮無向邊的情況下，最多能有多長的有向路徑
int f[maxn]; // f[i]是指以i為root的子樹裡都是有向邊(forward)時，最長鏈不超過maxUndirLen的條件下的最小值
int b[maxn]; // b[i]是指以i為root的子樹裡都是有向邊(backward)時，最長鏈不超過maxUndirLen的條件下的最小值
bool p[maxn]; // 紀錄節點是否有parent


bool readData()
{
    bool haveData = false;
    int u, v;
    char chDir;
    n = 0;
    
    G.assign(maxn + 5, {});

    memset(p, false, sizeof(p));

    while (scanf("%d", &u) && u)
    {
        haveData = true;
        if (u > n)
            n = u; // 維護到底有多少節點
        
        while (scanf("%d%c", &v, &chDir) && v)
        {
            if (v > n)
                n = v; // 維護到底有多少節點
            p[v] = true;

            if (chDir == 'd')
            {
                G[u].push_back({u, v, 1}); // forward
                G[v].push_back({v, u, 2}); // backward 
            }
            else if (chDir == 'u')
            {
                G[u].push_back({u, v, 2}); // backward
                G[v].push_back({v, u, 1}); // forward
            }
            else
            {
                // 只存u <-> v，不存v <-> u
                // 是因為接下來我們希望root是沒有parent
                // 而v在上面會被標記有parent
                // 所以只存u <-> v
                // u才可能沒有parent
                G[u].push_back({u, v, 0}); // undirected
            }
        }
    }

    if (haveData)
    {
        for (int i = 1; i <= n; ++i)
        {
            if (!p[i] && !G[i].empty())
            {
                root = i; // root沒有parent，且有子樹
                break;
            }
        }
    }

    return haveData;
}


int dfs(int u) // 不考慮無向邊，只走有向邊，找最長的有向路徑
{
    int res = 0;
    for (Edge& edge: G[u])
    {
        if (edge.dir == 1) // forward
            res = max(res, dfs(edge.v) + 1);
    }
    return res;
}


bool dp(int u, int parent)
{
    if (G[u].empty()) // 葉節點
    {
        f[u] = b[u] = 0;
        return true;
    }

    vector<UndirectedEdgeItem> undirChildren; // 存著有哪些無向邊，後面要處理
    int currF = 0;
    int currB = 0;

    for (Edge& edge: G[u])
    {
        if (edge.v == parent)
            continue;
        
        // 先往子樹求dp
        dp(edge.v, u);

        if (edge.dir == 0) // undirected
            undirChildren.push_back({edge.v, f[edge.v], b[edge.v]});
        else if (edge.dir == 1)
            currF = max(currF, f[edge.v] + 1);
        else
            currB = max(currB, b[edge.v] + 1);
    }

    if (undirChildren.empty()) // 沒有無向邊，不用討論定方向
    {
        f[u] = currF;
        b[u] = currB;
        // u當作中繼點，比之前找到的maxUndirLen還長，答案就是要maxUndirLen + 1
        if (f[u] + b[u] > maxUndirLen)
            f[u] = b[u] = 0x3f3f3f3f;

        return f[u] < 0x3f3f3f3f;
    }

    // 開始嘗試透過定無向邊方向使f[u] + b[u] <= maxUndirLen
    f[u] = b[u] = 0x3f3f3f3f;

    int m = undirChildren.size(); // 有m個無向邊要處理

    /*
        這裡有一個很重要的優化
        在求f[u]時目標是讓ff + bb <= maxUndirLen的條件之下ff最小
        其中ff是子樹中forward最長鏈
        bb是子樹中backward最長鏈
        首先我們將f由小到大排序
        假定我們將f第k小的邊定向為forward
        此時最好"順便"將f前k小的邊全部變成forward
        是因為前k - 1個邊的f全都比第k個邊小，
        所以此時枚舉的ff不會變大，而bb可能會變小
        因此只要枚舉一遍k找到第k + 1 ~ n個邊裡最大的bb
        求ff + bb + 1是否能夠 <= maxUndirLen即可，O(n)
        
        求b[u]時過程一樣，對b做排序，枚舉k即可，O(n)
    */

    // 先處理定向成forward
    // 照f排序
    sort(undirChildren.begin(), undirChildren.end(), [](const UndirectedEdgeItem& a, const UndirectedEdgeItem& b) {
        return a.f < b.f;
    });
    
    int maxRightB[maxn]; // 包含自己的右邊最大有多長的backward路徑
    maxRightB[m - 1] = undirChildren[m - 1].b;
    for (int k = m - 2; k >= 0; --k)
        maxRightB[k] = max(undirChildren[k].b, maxRightB[k + 1]); // 快速知道k + 1 ~ n裡最大的b
    
    for (int k = 0; k <= m; ++k) // 枚舉k
    {
        int ff = currF, bb = currB; // 繼承自有向邊的最大ff與bb，因為他們可能原本就是最長的
        if (k > 0)
            ff = max(ff, undirChildren[k - 1].f + 1); // 前k個邊都定向為forward
        if (k < m)
            bb = max(bb, maxRightB[k] + 1); // 找第k + 1 ~ n裡最大的bb
        
        if (ff + bb <= maxUndirLen)
            f[u] = min(f[u], ff); // 最長鏈裡的最小值
    }

    // 再處理定向成backward
    // 照b排序
    sort(undirChildren.begin(), undirChildren.end(), [](const UndirectedEdgeItem& a, const UndirectedEdgeItem& b) {
        return a.b < b.b;
    });
    int maxRightF[maxn]; // 包含自己的右邊最大有多長的forward路徑
    maxRightF[m - 1] = undirChildren[m - 1].f;
    for (int k = m - 2; k >= 0; --k) // 快速知道k + 1 ~ n裡最大的f
        maxRightF[k] = max(undirChildren[k].f, maxRightF[k + 1]);
    
    for (int k = 0; k <= m; ++k) // 枚舉k
    {
        int ff = currF, bb = currB;
        if (k > 0)
            bb = max(bb, undirChildren[k - 1].b + 1);  // 前k個邊都定向為backward
        if (k < m)
            ff = max(ff, maxRightF[k] + 1); // 找第k + 1 ~ n裡最大的ff
        
        if (ff + bb <= maxUndirLen)
            b[u] = min(b[u], bb); // 最長鏈裡的最小值
    }

    return f[u] < 0x3f3f3f3f;
}


int main()
{
    while (readData())
    {
        maxUndirLen = 0;
        for (int u = 1; u <= n; ++u)
            maxUndirLen = max(maxUndirLen, dfs(u));
        
        // +1是因為maxUndirLen數的是邊數，答案要點數
        if (dp(root, -1))
            printf("%d\n", maxUndirLen + 1); 
        else
            printf("%d\n", maxUndirLen + 2);
    }

    return 0;
}