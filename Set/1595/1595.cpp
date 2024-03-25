#include <cstdio>
#include <set>
using namespace std;

struct Point
{
    int x, y;
    bool operator < (const Point& other) const
    {
        if (this->x == other.x)
        {
            return this->y < other.y;
        }
        return this->x < other.x;
    }
} points[1005];

set<Point> pointSet;

int main()
{
    int T, N;
    scanf("%d", &T);
    while (T--)
    {
        pointSet.clear();
        scanf("%d", &N);
        int minX = 0x3f3f3f3f;
        int maxX = -0x3f3f3f3f;
        for (int i = 0; i < N; ++i)
        {
            scanf("%d %d", &points[i].x, &points[i].y);
            points[i].x *= 2;
            if (points[i].x > maxX)
                maxX = points[i].x;
            if (points[i].x < minX)
                minX = points[i].x;
            pointSet.insert(points[i]);
        }
        int mid = (minX + maxX) / 2;

        bool ok = true;
        Point t;
        for (int i = 0; i < N; ++i)
        {
            t.x = 2 * mid - points[i].x;
            t.y = points[i].y;
            if (!pointSet.count(t))
            {
                ok = false;
                break;
            }
        }

        printf("%s\n", (ok) ? "YES" : "NO");
    }
    return 0;
}