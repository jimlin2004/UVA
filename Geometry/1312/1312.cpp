#include <cstdio>
#include <algorithm>
using namespace std;

/*
    幾何 + 枚舉(sort + 微暴力)

    見 說明.png

    將點用先x再y的方式sort
    再紀錄points的y到y[]
    一樣sort過後unique去掉重複的減少計算
    枚舉以y[i]與y[j](i < j -> y[i] < y[j]因為sort+unique過)
    兩水平線的區間中能建出來的最大正方形
    其中能建出來的最大正方形會受到水平區間中的點與兩水平區間的高度限制

    所以暴力
    用雙層for loop去枚舉所有的水平區間
    對於每個水平區間去枚舉所有的點(再一個for loop)
    由於points sort過，所以依序枚舉到的點會是先x再y的順序
    一個變數curX紀錄當前檢查到水平區間的x(一開始curX = 0)
    每個點先檢查是否處於水平區間中(若否 -> 忽略)
    否則找到的那些點x會遞增(因為sort過)
    若當前找到點points[p]
    則當前子區間(一定是矩形)的大小為
    width: (points[p] - curX), height: (y[j] - y[i]) <- 兩水平線高度
    因此在此子區間的最大正方形寬度為min((points[p] - curX), (y[j] - y[i]))
    且此正方形的左下角座標為(curX, y[i])
    記得更新curX = points[p]以此換成下一個子區間

    一路枚舉下去，最後可得答案
*/

//多開10，因為y[]會多兩個
#define maxn 110

struct Point
{
    int x, y;
    bool operator < (const Point& other) const
    {
        if (this->x == other.x)
            return this->y < other.y;
        return this->x < other.x;
    }
};

Point points[maxn];
//額外將points的y記下來，方便後面搜尋
int y[maxn];

int maxW = -1;
Point res;
bool first = true;

void solve(int n, int width)
{
    maxW = -1;
    sort(points, points + n);
    sort(y, y + n + 2);
    int ySize = unique(y, y + n + 2) - y;

    for (int i = 0; i < ySize; ++i)
    {
        for (int j = i + 1; j < ySize; ++j)
        {
            //水平線高度
            int h = y[j] - y[i];
            int curX = 0;
            int w;
            for (int p = 0; p < n; ++p)
            {
                //不在當前的水平線區間內->忽略
                if (points[p].y <= y[i] || y[j] <= points[p].y)
                    continue;
                w = points[p].x - curX;
                w = min(w, h);
                if (maxW < w)
                {
                    maxW = w;
                    res.x = curX;
                    res.y = y[i];
                }
                curX = points[p].x;
            }
            //記得檢查curX到網格最右邊的那個區間內的最大方形
            w = min(width - curX, h);
            if (maxW < w)
            {
                maxW = w;
                res.x = curX;
                res.y = y[i];
            }
        }
    }

    if (first)
        first = false;
    else
        puts("");

    printf("%d %d %d\n", res.x, res.y, maxW);
}

int main()
{
    int n, width, height;
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d %d", &n, &width, &height);
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d", &points[i].x, &points[i].y);
            y[i] = points[i].y;
        }

        //要多添加上網格的地板與最上層，後面會unique所以重複沒差
        y[n] = 0;
        y[n + 1] = height;

        solve(n, width);
    }
    return 0;
}