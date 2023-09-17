#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
using namespace std;

vector<int> G[30];
vector<int> parent[30];
vector<int> sources;
bool visited[30] = {false};
int w[30] = {0};

struct Node
{
    int val;
    bool operator < (const Node& other) const
    {
        return w[this->val] > w[other.val];
    }
};

bool valid(int v)
{
    for (int p: parent[v])
    {
        if (visited[p] == false)
            return false;
    }
    return true;
}

int bfs()
{
    priority_queue<Node> pq;
    queue<int> Q;
    int res = 0;
    int current;
    for (int source: sources)
        pq.push({source});
    while (!pq.empty())
    {
        current = pq.top().val;
        pq.pop();
        res += w[current];
        visited[current] = true;
        while (!pq.empty())
        {
            Q.push(pq.top().val);
            pq.pop();
        }
        for (int child: G[current])
        {
            if (valid(child) && !visited[child])
            {
                pq.push({child});
            }
        }
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            w[u] -= w[current];
            if (w[u] == 0)
            {
                visited[u] = true;
                for (int child: G[u])
                {
                    if (valid(child) && !visited[child])
                    {
                        pq.push({child});
                    }
                }
            }
            else
                pq.push({u});
        }
        w[current] = 0;
    }
    return res;
}

void init()
{
    for (int i = 0; i < 30; ++i)
    {
        G[i].clear();
        parent[i].clear();
        w[i] = 0;
        visited[i] = false;
    }
    sources.clear();
}

int main()
{
    int T;
    bool flag = false;
    cin >> T;
    cin.get();
    cin.get();
    char u, v;
    int source;
    string buffer;
    while (T--)
    {
        if (flag)
            puts("");
        else
            flag = true;
        while (getline(cin, buffer))
        {
            if (buffer == "")
                break;
            stringstream ss(buffer);
            ss >> u;
            ss >> w[u - 'A'];

            while (ss >> v)
            {
                G[v - 'A'].push_back(u - 'A');
                parent[u - 'A'].push_back(v - 'A');
            }
            if (parent[u - 'A'].size() == 0)
            {
                sources.push_back(u - 'A');
            }
        }
        printf("%d\n", bfs());
        init();
    }
    return 0;
}

/*
2

A 5
B 3 A
D 2 A
C 2 B
F 2 CE
E 4 DC

A 5
B 3 A
D 2 A
C 2 B
F 2 CE
E 4 DC

*/