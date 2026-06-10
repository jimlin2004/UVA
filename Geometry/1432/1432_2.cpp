#include <bits/stdc++.h>
using namespace std;

/*
題意:
    求能夠涵蓋k個點的最小扇形面積

解法:
    枚舉所有可能的R，在固定的半徑下用滑動窗戶找最小的夾角

    稍微剪枝加枚舉，需要O(n^2)
*/


#define maxn 5005

struct Point
{
    double x, y;
    int cnt;
    double radian;
    double radius;
};

const double PI = acos(-1);
Point points[maxn];
int n, k;

// 用來記得哪些點能夠被覆蓋
Point covered[2 * maxn];

double solve()
{
    // 答案都是 0.00
    if (k <= 1)
        return 0;

    // 依照角度由小到大排序
    sort(points, points + n, [](const Point& a, const Point& b) {
        return a.radian < b.radian;
    });

    // 用來記哪些半徑搜過了
    unordered_map<double, bool> vis;

    double res = 0x3f3f3f3f;

    // 枚舉每個點的距離作為扇形的半徑
    for (int i = 0; i < n; ++i)
    {
        // 剪枝1: 以此半徑畫圓都不能覆蓋k個點以上 -> 跳過
        if (points[i].cnt < k)
            continue;
        // 剪枝2: 若這個半徑搜過了，沒必要再搜一次
        if (vis[points[i].radius])
            continue;

        vis[points[i].radius] = true;

        // 當前半徑
        double currR = points[i].radius;
        double minRadian = 0x3f3f3f3f;
        int m = 0; // 有多少點被覆蓋

        // 過濾出所有在當前半徑範圍內的點，並放入 covered 陣列
        for (int j = 0; j < n; ++j)
        {
            if ((points[j].radius < currR) || (fabs(points[j].radius - currR) < 1e-9))
            {
                covered[m] = points[j];
                ++m;
                // 滑動窗戶: 已經蒐集的點數量 >= k時，計算頭尾的角度差
                if (m >= k)
                {
                    minRadian = min(minRadian, covered[m - 1].radian - covered[m - k].radian);
                }
            }
        }

        // 防禦性檢查
        if (m < k)
            continue;
        
        // 處理跨越極軸（0度/360度邊界）的循環情況
        // 因為 covered 陣列是線性的，我們需要檢查首尾相接的連續 k 個點
        // 複製成兩倍陣列，處理循環陣列問題
        for (int j = 0; j < m; ++j)
            covered[j + m] = covered[j];
        
        // 處理循環陣列問題
        for (int j = m; j < m + k; ++j)
        {
            // 注意由於程式可讀性考量，這裡用的角度相減是負的，需要加上2pi
            minRadian = min(minRadian, covered[j].radian - covered[j - k + 1].radian + 2 * PI);
        }

        // 更新最小扇形面積
        res = min(res, (minRadian / 2) * currR * currR);
    }
    return res;
}


int main()
{
    int Case = 0;

    while (scanf("%d %d", &n, &k))
    {
        if (n == 0 && k == 0)
            break;
        
        for (int i = 0; i < n; ++i)
        {
            scanf("%lf %lf", &points[i].x, &points[i].y);

            // 由於atan2是從第三象限開始繞一圈變大
            // 理論上不影響計算，但這邊做一個變成從第一象限開始繞一圈變大的處理
            // 因為atan2的回傳是[-π, π]，加上π讓範圍變成[0, 2π]
            if (points[i].y < 0)
                points[i].radian = atan2(-points[i].y, -points[i].x) + PI;
            else
                points[i].radian = atan2(points[i].y, points[i].x);

            points[i].radius = sqrt((points[i].x * points[i].x) + (points[i].y * points[i].y));
        }

        // 依照半徑由小到大排序
        sort(points, points + n, [](const Point& a, const Point& b) {
            return a.radius < b.radius;
        });

        // 已經半徑由小到大排序，所以可以簡單知道以每個點距離當半徑畫整個圓能夠涵蓋幾個點
        for (int i = 0; i < n; ++i)
            points[i].cnt = i + 1;
        
        printf("Case #%d: %.2lf\n", ++Case, solve());
    }

    return 0;
}