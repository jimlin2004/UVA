#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define maxn 1005

struct Point
{
    int x, y;
    double radian;
    bool isBlack;
    bool operator < (const Point& other)
    {
        return this->radian < other.radian;
    }
};

//原來坐標系的點
Point originPoints[maxn];
//新坐標系的點
Point newPoints[maxn];

int crossProduct(const Point& O, const Point& A, const Point& B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

int solve(int n)
{
    if (n <= 2)
        return 2;
    int res = 0;
    //枚舉每個點作為基準點
    for (int i = 0; i < n; ++i)
    {
        int newPointSize = 0;
        //以i為基準點，做座標變換，並算極角
        //在新的坐標系中，originPoints[i]變成原點
        for (int j = 0; j < n; ++j)
        {
            if (j != i)
            {
                newPoints[newPointSize].x = originPoints[j].x - originPoints[i].x;
                newPoints[newPointSize].y = originPoints[j].y - originPoints[i].y;
                //將黑點變成白色的對稱點，如此就不用計算兩邊的黑與白，只要計算在左側的白點個數
                //等式移項的概念
                if (originPoints[j].isBlack)
                {
                    newPoints[newPointSize].x *= -1;
                    newPoints[newPointSize].y *= -1;
                }
                newPoints[newPointSize].radian = atan2(newPoints[newPointSize].y, newPoints[newPointSize].x);
                ++newPointSize;
            }
        }

        //以極角排序
        sort(newPoints, newPoints + newPointSize);
    
        //極角掃描，count是在基準點至newPoints[L]方向左側的點數量(包含線上)
        //有點滑動窗戶的概念，只更新頭尾，中間不重算
        int L = 0, R = 0, count = 2;
        while (L < newPointSize)
        {
            //一開始的L == R會在後面減回來
            if (R == L)
            {
                R = (R + 1) % newPointSize;
                ++count;
            }
            //OL 到 OR
            //crossProduct > 0相當於逆時針，也就是在左側
            //crossProduct = 0 為共線
            static Point originPoint = {0, 0, 0};
            while (R != L && (crossProduct(originPoint, newPoints[L], newPoints[R]) >= 0))
            {
                R = (R + 1) % newPointSize;
                ++count;
            }
            
            --count;//減回剛剛多加的(一開始的R == L)
            ++L;
            res = max(res, count);
        }
    }
    return res;
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF && n)
    {
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d %d", &originPoints[i].x, &originPoints[i].y, &originPoints[i].isBlack);
        }
        printf("%d\n", solve(n));
    }
    return 0;
}