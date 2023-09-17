#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int toNode[26]; // char to int
int toChar[26]; // int to char
bool visited[26];
int indegree[26];
vector<vector<int>> G;
int nodeNum;

void topological(vector<char> order) // kahn
{
    if (order.size() == nodeNum)
    {
        for (char c: order)
            printf("%c", c);
        puts("");
        return;
    }
    
    for (int u = 0; u < nodeNum; ++u)
    {
        if (indegree[u] == 0 && !visited[u])
        {
            visited[u] = true;
            order.emplace_back(toChar[u]);
            for (int v: G[u])
                --indegree[v];
            
            topological(order);

            for (int v: G[u])
                ++indegree[v];
            visited[u] = false;
            order.pop_back();
        }
    }
}

int main()
{
    char input[400];
    char* token;
    int u, v;
    bool flag = false;
    while (fgets(input, 400, stdin) != NULL)
    {
        G.assign(26, vector<int>());
        memset(toNode, -1, sizeof(toNode));
        memset(toChar, -1, sizeof(toChar));
        memset(visited, false, sizeof(visited));
        memset(indegree, 0, sizeof(indegree));
        int nodeIndex = 0;
        nodeNum = 0;
        
        vector<char> inputVec;
        token = strtok(input, " ");
        
        while (token != NULL)
        {
            
            inputVec.emplace_back(token[0]);
            token = strtok(NULL, " ");
        }

        sort(inputVec.begin(), inputVec.end());

        for (char c: inputVec)
        {
            toNode[c - 'a'] = nodeIndex;
            toChar[nodeIndex] = c;
            ++nodeIndex;
            ++nodeNum;
        }

        fgets(input, 400, stdin);

        //第一筆pair
        u = strtok(input, " ")[0] - 'a';
        v = strtok(NULL, " ")[0] - 'a';
        G[toNode[u]].emplace_back(toNode[v]);
        ++indegree[toNode[v]];
        while (1)
        {
            token = strtok(NULL, " ");
            if (token == NULL)
                break;
            u = token[0] - 'a';
            v = strtok(NULL, " ")[0] - 'a';
            G[toNode[u]].emplace_back(toNode[v]);
            ++indegree[toNode[v]];
        }

        if (flag)
            puts("");
        else
            flag = true;

        topological({});
    }
    return 0;
}