#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

vector<int> fireStations;
int dis[505][505];
int fireStationDis[505]; // 每個點到離它最近的消防局距離

void floydWarshall(int n)
{
    for (int k = 1; k <= n; ++k)
    {
        dis[k][k] = 0;
        for (int x = 1; x <= n; ++x)
        {
            for (int y = 1; y <= n; ++y)
                dis[x][y] = min(dis[x][y], dis[x][k] + dis[k][y]);
        }
    }
}

int main()
{
    int t;
    int f, n;
    bool flag = false;

    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;
    
    while (t--)
    {
        cin >> f >> n;
        fireStations.clear();
        memset(dis, 0x3f, sizeof(dis));
        memset(fireStationDis, 0x3f, sizeof(fireStationDis));
        for (int i = 0; i < f; ++i)
        {
            int fireStation;
            cin >> fireStation;
            fireStations.emplace_back(fireStation);
        }

        string str;
        int u, v, w;
        stringstream ss;
        getline(cin, str);
        while (getline(cin, str) && !str.empty())
        {
            ss.clear();
            ss.str("");
            ss << str;
            ss >> u >> v >> w;
            dis[u][v] = dis[v][u] = w;
        }

        //算出所有村莊之間距離
        floydWarshall(n);

        //算出每個村莊到與它最近的消防局距離
        for (int i = 1; i <= n; ++i)
        {
            for (int fireStation: fireStations)
            {
                fireStationDis[i] = min(fireStationDis[i], dis[i][fireStation]);
            }
        }

        //枚舉新點
        int res;
        int minimalMaxDis = 0x3f3f3f3f;
        int newMinDis;//在添加新點後，該點到消防局的最短距離
        for (int newFireStation = 1; newFireStation <= n; ++newFireStation)
        {
            int currMax = -1;
            for (int v = 1; v <= n; ++v)
            {
                if (v == newFireStation)
                    continue;
                currMax = max(currMax, min(fireStationDis[v], dis[v][newFireStation]));
            }

            if (currMax < minimalMaxDis)
            {
                res = newFireStation;
                minimalMaxDis = currMax;
            }
        }

        if (flag)
            cout << '\n';
        else
            flag = true;
        cout << res << '\n';
    }
    return 0;
}