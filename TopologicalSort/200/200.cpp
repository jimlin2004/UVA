#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

/*
題意是輸入是一個類似書目的列表，所以每兩行暗示著字母的大小關係
ex:
    XWY
    ZX
    -> X < Z
    ZX
    ZXY
    -> 沒有結論
    ZXY
    ZXW
    -> Y < W
    ZXW
    YWWX
    -> Z < Y
    所以得到
    XZYW是正確的大小關係
    -> 拓樸排序
*/

int indegree[30];
//曾經出現過
bool used[30];
vector<vector<int>> G;

void kahn()
{
    queue<int> q;
    for (int i = 0; i < 30; ++i)
    {
        if (indegree[i] == 0 && used[i])
            q.push(i);
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        printf("%c", (u + 'A'));
        for (int v: G[u])
        {
            --indegree[v];
            if (indegree[v] == 0)
                q.push(v);
        }
    }

    puts("");
}

int main()
{
    string line1;
    string line2;
    cin >> line1;
    G.assign(30, vector<int>());
    while (cin >> line2 && line2 != "#")
    {
        int len = min(line1.size(), line2.size());
        for (int i = 0; i < len; ++i)
        {
            used[line1[i] - 'A'] = true;
            used[line2[i] - 'A'] = true;
            if (line1[i] != line2[i])
            {
                G[line1[i] - 'A'].emplace_back(line2[i] - 'A');
                ++indegree[line2[i] - 'A'];
                break;
            }
        }
        line1 = line2;
    }

    kahn();
    return 0;
}