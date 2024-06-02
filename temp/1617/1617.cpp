#include <iostream>
#include <algorithm>
using namespace std;

#define maxn 300005

struct Segment
{
    int l, r;
    bool operator < (const Segment& other) const
    {
        if (this->r == other.r)
            return this->l < other.l;
        return this->r < other.r;
    }
};

Segment segments[maxn];

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d", &segments[i].l, &segments[i].r);
        }

        sort(segments, segments + n);

        int currR = segments[0].r;
        int res = 0;
        for (int i = 1; i < n; ++i)
        {
            if (segments[i].r == currR)
                continue;
            else if (currR < segments[i].l)
            {
                currR = segments[i].r;
                ++res;
            }
            else
            {
                ++currR;
            }
        }

        printf("%d\n", res);
    }
    return 0;
}
