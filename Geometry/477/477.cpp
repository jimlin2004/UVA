#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

#define eps 1e-6

class Point
{
public:
    double x, y;
    Point() = default;
    Point(double x, double y)
        : x(x)
        , y(y)
    {
    }

    inline double getDis(const Point& other) const
    {
        return sqrt((this->x - other.x) * (this->x - other.x) + (this->y - other.y) * (this->y - other.y));
    }
};

class Shape
{
public:
    virtual bool isContain(const Point& point) const = 0;
};

class Rect: public Shape
{
private:
    double xmin, ymin, xmax, ymax;
public:
    Rect(double x1, double y1, double x2, double y2)
        : xmin(x1), ymin(y2)
        , xmax(x2), ymax(y1)
    {
    }

    bool isContain(const Point& point) const override
    {
        return (((this->xmin < point.x || abs(this->xmin - point.x) < eps) && (point.x < this->xmax || abs(point.x - this->xmax) < eps))
            && ((this->ymin < point.y || abs(this->ymin - point.y) < eps) && (point.y < this->ymax || abs(point.x - this->ymax) < eps)));
    }
};

class Circle: public Shape
{
private:
    Point center;
    double r;
public:
    Circle(double x, double y, double r)
        : center(x, y), r(r)
    {
    }

    bool isContain(const Point& point) const override
    {
        double dis = this->center.getDis(point);
        return (dis < this->r) || (abs(dis - this->r) < eps);
    }
};

vector<Shape*> shapes;

int main()
{
    char type;
    while (scanf("%c", &type) != EOF && type != '*')
    {
        if (type == 'r')
        {
            double x1, y1, x2, y2;
            scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
            shapes.push_back(new Rect(x1, y1, x2, y2));
        }
        else if (type == 'c')
        {
            double x, y, r;
            scanf("%lf %lf %lf", &x, &y, &r);
            shapes.push_back(new Circle(x, y, r));
        }
    }

    double x, y;
    int pointCount = 0;
    while (scanf("%lf %lf", &x, &y) != EOF)
    {
        if (abs(x - 9999.9) < eps && abs(y - 9999.9) < eps)
            break;
        ++pointCount;
        Point point(x, y);
        bool ok = false;
        for (int i = 0; i < shapes.size(); ++i)
        {
            Shape* shape = shapes[i];
            if (shape->isContain(point))
            {
                ok = true;
                printf("Point %d is contained in figure %d\n", pointCount, i + 1);
            }
        }

        if (!ok)
        {
            printf("Point %d is not contained in any figure\n", pointCount);
        }
    }
    return 0;
}