#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

//經典對起點、終點做dijkstar，並枚舉新路的題目

#define maxn 505

struct Edge
{
    int u, v, w;
};

struct HeapItem
{
    int u, dis;
    bool operator < (const HeapItem& other) const
    {
        return this->dis > other.dis;
    }
};

int disFromSource[maxn];
int disFromTarget[maxn];
int parentFromSource[maxn];
int parentFromTarget[maxn];
bool visited[maxn];
vector<vector<Edge>> G;

void dijkstar(int source, int disArray[], unsigned int disArratSize, int parentArray[], unsigned int parentArraySize)
{
    memset(visited, false, sizeof(visited));
    memset(disArray, 0x3f, disArratSize);
    memset(parentArray, -1, parentArraySize);
    priority_queue<HeapItem> pq;
    disArray[source] = 0;
    pq.push({source, 0});
    while (!pq.empty())
    {
        HeapItem currItem = pq.top();
        pq.pop();
        visited[currItem.u] = true;
        for (const Edge& edge: G[currItem.u])
        {
            if (visited[edge.v])
                continue;
            if (disArray[edge.v] > disArray[currItem.u] + edge.w)
            {
                disArray[edge.v] = disArray[currItem.u] + edge.w;
                parentArray[edge.v] = edge.u;
                pq.push({edge.v, disArray[edge.v]});
            }
        }
    }
}

void printPathToSource(int source, int target, int parentArray[])
{
    if (parentArray[source] == -1)
        return;
    if (source == target)
        return;
    printPathToSource(parentArray[source], target, parentArray);
    cout << ' ' << source;
}

void printPathToTarget(int source, int target, int parentArray[])
{
    if (parentArray[source] == -1)
        return;
    if (source == target)
        return;
    cout << ' ' << source;
    printPathToTarget(parentArray[source], target, parentArray);
}

int main()
{
    int N, S, E;
    bool first = true;
    //題目用空白行分開test case，scanf太麻煩，改用cin
    while (cin >> N >> S >> E)
    {
        int M;
        cin >> M;
        int u, v, w;
        G.assign(N + 5, vector<Edge>());
        for (int i = 0; i < M; ++i)
        {
            cin >> u >> v >> w;
            G[u].emplace_back(Edge{u, v, w});
            G[v].emplace_back(Edge{v, u, w});
        }
        dijkstar(S, disFromSource, sizeof(disFromSource), parentFromSource, sizeof(parentFromSource));
        dijkstar(E, disFromTarget, sizeof(disFromTarget), parentFromTarget, sizeof(parentFromTarget));
        
        int k;
        cin >> k;
        Edge newEdge;
        Edge ansEdge;
        int useTicketAt = -1;
        //先設為不用飛機票的
        int shortestDis = disFromSource[E];
        while (k--)
        {
            cin >> newEdge.u >> newEdge.v >> newEdge.w;
            //試試看用ticket會不會更好
            int temp = disFromSource[newEdge.u] + newEdge.w + disFromTarget[newEdge.v];
            if ((disFromSource[newEdge.u] + newEdge.w + disFromTarget[newEdge.v]) < shortestDis)
            {
                shortestDis = disFromSource[newEdge.u] + newEdge.w + disFromTarget[newEdge.v];
                useTicketAt = newEdge.u;
                ansEdge = newEdge;
            }
            //反路
            if ((disFromSource[newEdge.v] + newEdge.w + disFromTarget[newEdge.u]) < shortestDis)
            {
                shortestDis = disFromSource[newEdge.v] + newEdge.w + disFromTarget[newEdge.u];
                useTicketAt = newEdge.v;
                ansEdge = {newEdge.v, newEdge.u, newEdge.w};
            }
        }

        if (first)
            first = false;
        else
            cout << '\n';
        if (useTicketAt != -1)
        {
            cout << S;
            printPathToSource(ansEdge.u, S, parentFromSource);
            printPathToTarget(ansEdge.v, E, parentFromTarget);
            cout << ' ' << E;
            cout << '\n';
            cout << useTicketAt << '\n';
            cout << shortestDis << '\n';
        }
        else
        {
            cout << S;
            printPathToSource(E, S, parentFromSource);
            cout << '\n';
            cout << "Ticket Not Used" << '\n';
            cout << shortestDis << '\n';
        }
    }
    return 0;
}

/*
4 1 4
4
1 2 2
1 3 3
2 4 4
3 4 5
1
2 4 3
*/