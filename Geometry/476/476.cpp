#include <cstdio>

//用分離軸判斷法

struct Rect
{
    double minX, minY, maxX, maxY;
    bool isContain(double x, double y)
    {
        bool xAxisCheck = (this->minX < x && x < this->maxX);
        bool yAxisCheck = (this->minY < y && y < this->maxY);
        return xAxisCheck && yAxisCheck;
    }
};

Rect rects[15];

int main()
{
    char cmd = 0;
    int rectCount = 0;
    while (scanf("%c", &cmd) && cmd != '*')
    {
        double x1, y1, x2, y2;
        scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
        rects[rectCount].minX = x1;
        rects[rectCount].minY = y2;
        rects[rectCount].maxX = x2;
        rects[rectCount].maxY = y1;
        ++rectCount;
        getchar(); // for \n
    }
    double x, y;
    int pointCount = 1;
    while (scanf("%lf %lf", &x, &y) != EOF && (x != 9999.9 && y != 9999.9))
    {
        bool ok = false;
        for (int i = 0; i < rectCount; ++i)
        {
            if (rects[i].isContain(x, y))
            {
                ok = true;
                printf("Point %d is contained in figure %d\n", pointCount, i + 1);
            }
        }
        if (!ok)
            printf("Point %d is not contained in any figure\n", pointCount);
        ++pointCount;
    }
    return 0;
}