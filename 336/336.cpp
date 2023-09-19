#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

bool visited[35];
unordered_map<int, int> nodeMap; //key: 原編號，value: node index
int nodeIndex;
vector<vector<int>> G;
int Case = 0;

int insertNodeToMap(int node)
{
    if (nodeMap.find(node) == nodeMap.end())
    {
        return nodeMap[node] = nodeIndex++;
    }
    else
        return nodeMap[node];
}

void bfs(int source, int TTL)
{
    memset(visited, false, sizeof(visited));
    queue<int> q;
    q.push(nodeMap[source]);
    int timer = 0;
    int stepSize;
    int current;
    while (!q.empty() && timer <= TTL)
    {
        stepSize = q.size();
        for (int i = 0; i < stepSize; ++i)
        {
            current = q.front();
            q.pop();
            visited[current] = true;
            for (int v: G[current])
            {
                if (visited[v])
                    continue;
                q.push(v);
            }
        }
        ++timer;
    }
    
    int res = 0;
    for (int i = 0; i < nodeMap.size(); ++i)
    {
        if (!visited[i])
            ++res;
    }

    printf("Case %d: %d nodes not reachable from node %d with TTL = %d.\n", ++Case, res, source, TTL);
}

int main()
{
    int NC;
    int u, v;
    int uIndex, vIndex;
    int source, TTL; 
    while (cin >> NC && NC != 0)
    {
        G.assign(35, vector<int>());
        nodeIndex = 0;
        nodeMap.clear();
        for (int i = 0; i < NC; ++i)
        {
            cin >> u >> v;
            uIndex = insertNodeToMap(u);
            vIndex = insertNodeToMap(v);
            G[uIndex].emplace_back(vIndex);
            G[vIndex].emplace_back(uIndex);
        }

        while (cin >> source >> TTL)
        {
            if (source == 0 && TTL == 0)
                break;
            bfs(source, TTL);
        }
    }
    return 0;
}