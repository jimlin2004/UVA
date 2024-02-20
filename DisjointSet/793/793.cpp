#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

//題目竟然不講最多幾個點?????????
vector<int> parent;
int yesCount = 0, noCount = 0;

int find(int x)
{
    if (parent[x] < 0)
        return x;
    return parent[x] = find(parent[x]);
}

void Union(int a, int b)
{
    int r1 = find(a);
    int r2 = find(b);
    if (r1 == r2)
        return;
    if (parent[r1] < parent[r2])
    {
        parent[r1] += parent[r2];
        parent[r2] = r1;
    }
    else
    {
        parent[r2] += parent[r1];
        parent[r1] = r2;
    }
}

int main()
{
    int t;
    cin >> t;
    bool first = true;
    while (t--)
    {
        int n;
        cin >> n;
        parent.assign(n + 5, -1);
        string line;
        int u, v;
        char cmd;
        stringstream ss;
        cin.ignore();
        while (getline(cin, line))
        {
            if (line.empty())
                break;
            ss << line;
            ss >> cmd >> u >> v;
            ss.clear();
            if (cmd == 'c')
                Union(u, v);
            else if (cmd == 'q')
            {
                if (find(u) == find(v))
                    ++yesCount;
                else
                    ++noCount;
            }
        }
        if (first)
            first = false;
        else
            cout << '\n';
        cout << yesCount << "," << noCount << "\n";
        yesCount = 0;
        noCount = 0;
    }
    return 0;
}