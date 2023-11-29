#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#define esp 1e-6
//凸包靶題 -> Graham's Scan、凸包面積、點是否在凸包內

struct Point
{
    int x, y;

    bool operator == (const Point& other) const
    {
        return this->x == other.x && this->y == other.y;
    }
};

//vec<OA> 與 vec<OB>的crossProduct
//res > 0 -> 順時針
//res < 0 -> 逆時針
//res = 0 -> 共線
int crossProduct(const Point& O, const Point& A, const Point& B)
{
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

double getDis(const Point& p1, const Point& p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

struct Item
{
    Point p;
    double theta;
    double dis;
    bool operator < (const Item& other) const
    {
        if (abs(this->theta - other.theta) <= esp)
        {
            return dis < other.dis;
        }
        return this->theta < other.theta;
    }
};

class ConvexHull
{
public:
    ConvexHull() = default;
    bool isDestoried = false;
    vector<Point> points;
    vector<Point> convexHullPoints;

    //Graham's Scan O(nlogn)
    void getConvexHull(const Point& startPoint)
    {
        vector<Item> pointsVec;
        for (const Point& p: this->points)
        {
            if (p == startPoint)
                continue;
            pointsVec.emplace_back(Item{p, atan2(p.y - startPoint.y, p.x - startPoint.x), getDis(startPoint, p)});
        }

        //照atan2排序
        sort(pointsVec.begin(), pointsVec.end());
        this->convexHullPoints.emplace_back(startPoint);

        for (const Item& item: pointsVec)
        {
            while (this->convexHullPoints.size() >= 2 &&
                (crossProduct(this->convexHullPoints[this->convexHullPoints.size() - 2], this->convexHullPoints[this->convexHullPoints.size() - 1], item.p) <= 0))
            {
                this->convexHullPoints.pop_back();
            }
            this->convexHullPoints.emplace_back(item.p);
        }
        return;
    }

    bool contain(const Point& targetPoint)
    {
        //都要是逆時針或共線
        for (int i = 0; i < this->convexHullPoints.size() - 1; ++i)
        {
            if (crossProduct(targetPoint, this->convexHullPoints[i], this->convexHullPoints[i + 1]) < 0)
                return false;
        }
        return (crossProduct(targetPoint, this->convexHullPoints[this->convexHullPoints.size() - 1], this->convexHullPoints[0]) >= 0);
    }

    //測量師公式
    double getArea()
    {
        int area = 0;
        int pointNum = this->convexHullPoints.size();
        for (int i = 0; i < pointNum - 1; ++i)
        {
            area += (this->convexHullPoints[i].x * this->convexHullPoints[i + 1].y) - (this->convexHullPoints[i].y * this->convexHullPoints[i + 1].x);
        }
        area += (this->convexHullPoints[pointNum - 1].x * this->convexHullPoints[0].y) - (this->convexHullPoints[pointNum - 1].y * this->convexHullPoints[0].x);
        return (((double)area) * 0.5);
    }
};

ConvexHull kingdoms[25];
int kingdomNum = 0;

int main()
{
    int n;
    Point p;
    Point startPoint; //最下面、最右邊的點
    while (scanf("%d", &n) && n != -1)
    {
        ++kingdomNum;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d", &p.x, &p.y);
            if (i == 0)
            {
                startPoint = p;
            }
            else
            {
                if (startPoint.y > p.y)
                {
                    if (startPoint.x > p.x)
                        startPoint = p;
                }
            }

            kingdoms[kingdomNum - 1].points.emplace_back(p);
        }
        kingdoms[kingdomNum - 1].getConvexHull(startPoint);
    }

    Point missilePoint;
    double totalArea = 0.0;
    while (scanf("%d %d", &missilePoint.x, &missilePoint.y) != EOF)
    {
        for (int i = 0; i < kingdomNum; ++i)
        {
            if (!kingdoms[i].isDestoried && kingdoms[i].contain(missilePoint))
            {
                kingdoms[i].isDestoried = true;
                totalArea += kingdoms[i].getArea();
            }
        }
    }
    
    printf("%.2lf\n", totalArea);
    return 0;
}