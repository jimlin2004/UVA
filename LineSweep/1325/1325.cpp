#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

/*
    這題只有一個問題
    因為答案一定是兩兩點連線的一個邊長
    但若是枚舉所有的邊長下去搜一遍最大的答案會超時

    這題要換個想法
    將所有的邊存起來並以長度由小到大排序
    只要由小的邊開始維護不穩定的星球數量
    當邊長改變時，先維護當前的答案
    一個重要的想法是在搜較長的邊時不用把較短的邊再搜一遍
    因為答案不會改變
    所以加速就在這裡
    只要對所有的邊搜一遍就行了
    算是掃描線法的概念
    
    細節看程式
*/

#define maxn 1005
#define eps 1e-9

struct Point
{
    int x, y, z;
    int p;
    Point(int x, int y, int z, int p): x(x), y(y), z(z), p(p)
    {}
};

struct Edge
{
    int i, j;
    double dis;
};

vector<Point> points;
vector<Edge> edges;
//state[i]存的是星球i可接收到同類的數量 - 異類的數量
//若為負數代表i是不穩定星球
int state[maxn];

inline double getDis(Point& p1, Point& p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z));
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        points.clear();
        edges.clear();

        //一開始所有星球可以看到自己的頻道，所以設為1
        for (int i = 0; i < n; ++i)
            state[i] = 1;

        int x, y, z, p;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d %d %d", &x, &y, &z, &p);

            points.emplace_back(x, y, z, p);
        }

        //兩兩點建邊
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                double dis = getDis(points[i], points[j]);
                edges.push_back({i, j, dis});
            }
        }

        //邊依長度由小到大排
        sort(edges.begin(), edges.end(), [&](Edge& e1, Edge& e2) {
            return e1.dis < e2.dis;
        });

        //最好答案
        int resD = 0;
        double resR = 0.0;
        //當前不穩定的星球數量
        int currD = 0;
        for (int k = 0; k < edges.size(); ++k)
        {
            //同類
            if (points[edges[k].i].p == points[edges[k].j].p)
            {
                //當state[i]從-1變0就不是不穩定星球，所以curr -= 1
                if (state[edges[k].i] == -1)
                    --currD;
                ++state[edges[k].i];
                if (state[edges[k].j] == -1)
                    --currD;
                ++state[edges[k].j];
            }
            else
            {
                //當state[i]從0變-1就產生新的不穩定星球，所以curr += 1
                if (state[edges[k].i] == 0)
                    ++currD;
                --state[edges[k].i];
                if (state[edges[k].j] == 0)
                    ++currD;
                --state[edges[k].j];
            }
            
            //當現在的邊與下個邊長度一樣就代表還沒搜完當前搜尋的答案邊長
            if (k != edges.size() - 1 && fabs(edges[k].dis - edges[k + 1].dis) < eps)
                continue;

            //維護答案
            if (currD > resD)
            {
                resD = currD;
                resR = edges[k].dis;
            }
            else if (currD == resD && resR > edges[k].dis)
            {
                resR = edges[k].dis;
            }
        }

        printf("%d\n", resD);
        printf("%.4lf\n", resR);
    }
    return 0;
}

/*
4
0 0 0 1
0 1 0 0
1 0 0 0
1 1 0 1
4
0 0 0 1
1 0 0 0
0 1 0 0
0 0 1 1
*/