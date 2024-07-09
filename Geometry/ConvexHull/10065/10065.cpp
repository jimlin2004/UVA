#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

//凸包+面積公式

#define maxn 105

int ox;
int oy;
int x[maxn];
int y[maxn];

double getDis(int px, int py)
{
    return sqrt((px - ox) * (px - ox) + (py - oy) * (py - oy));
}

struct Point
{
    int x, y;
    double dis;
    double rad;

    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
        this->rad = atan2(this->y - oy, this->x - ox);
        this->dis = getDis(this->x, this->y);
    }

    bool operator == (const Point& other) const
    {
        return (this->x == other.x) && (this->y == other.y);
    }

    bool operator < (const Point& other) const
    {
        if (this->rad == other.rad)
            return this->dis < other.dis;
        return this->rad < other.rad;
    }
};

vector<Point> points;

double getArea(vector<Point>& p)
{
    int area = 0;
    p.push_back(p[0]);
    for (int i = 1; i < p.size(); ++i)
    {
        area += ((p[i - 1].x * p[i].y) - (p[i - 1].y * p[i].x));
    }
    p.pop_back();
    return abs(area) * 0.5;
}

int crossProduce(const Point& a, const Point& b, const Point& c)
{
    int ux = b.x - a.x;
    int uy = b.y - a.y;
    int vx = c.x - a.x;
    int vy = c.y - a.y;
    return (ux * vy) - (uy * vx);
}

vector<Point> getConvexhull(const vector<Point>& p)
{
    vector<Point> convexhull;
    int sz = convexhull.size();
    for (int i = 0; i < p.size(); ++i)
    {
        while ((sz >= 2) && (crossProduce(convexhull[sz - 2], convexhull[sz - 1], p[i]) <= 0))
        {
            convexhull.pop_back();
            --sz;
        }
        convexhull.emplace_back(p[i]);
        ++sz;
    }
    return convexhull;
}

int main()
{
    int Case = 0;
    int n;
    while (scanf("%d", &n) && n)
    {
        points.clear();
        ox = 0x3f3f3f3f;
        oy = 0x3f3f3f3f;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d", &x[i], &y[i]);
            if (y[i] < oy)
            {
                ox = x[i];
                oy = y[i];
            }
            else if (y[i] == oy && x[i] < ox)
            {
                ox = x[i];
                oy = y[i];
            }
        }

        for (int i = 0; i < n; ++i)
        {
            points.emplace_back(x[i], y[i]);
        }
        double usedArea = getArea(points);
        sort(points.begin(), points.end());
        vector<Point> convexhull = getConvexhull(points);
        double convexhullArea = getArea(convexhull);
        printf("Tile #%d\n", ++Case);
        printf("Wasted Space = %.2lf %\n\n", (convexhullArea - usedArea) / convexhullArea * 100);
    }
    return 0;
}