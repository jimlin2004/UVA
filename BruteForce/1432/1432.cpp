#include <bits/stdc++.h>
using namespace std;

/*
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
Point covered[maxn];

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

    for (int i = 0; i < n; ++i)
    {
        // 算半徑都不能覆蓋k個點以上 -> 跳過
        if (points[i].cnt < k)
            continue;
        // 若這個半徑搜過了，沒必要再搜一次
        if (vis[points[i].radius])
            continue;

        vis[points[i].radius] = true;

        double currR = points[i].radius;
        double minRadian = 0x3f3f3f3f;
        int m = 0; // 有多少點被覆蓋

        // 數學上的正向旋轉搜一次
        for (int j = 0; j < n; ++j)
        {
            if ((points[j].radius < currR) || (fabs(points[j].radius - currR) < 1e-9))
            {
                covered[m] = points[j];
                ++m;
                if (m >= k)
                {
                    minRadian = min(minRadian, covered[m - 1].radian - covered[m - k].radian);
                }
            }
        }

        if (m < k)
            continue;
        
        // 數學上的逆向旋轉搜一次
        // 注意只需要從 0 ~ k - 2 開始搜，是因為k - 1開始會在正向旋轉的時候搜過了
        // 這裡是處理循環陣列的index問題，也能直接開成兩倍長的陣列
        for (int j = 0; j < k - 1; ++j)
        {
            // 注意由於程式可讀性考量，這裡用的角度相減是負的，需要加上2pi
            minRadian = min(minRadian, covered[j].radian - covered[m - k + j + 1].radian + 2 * PI);
        }

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

        // 已經由小到大排序，所以可以簡單知道以每個點畫半徑有機會涵蓋幾個點
        for (int i = 0; i < n; ++i)
            points[i].cnt = i + 1;
        
        printf("Case #%d: %.2lf\n", ++Case, solve());
    }

    return 0;
}