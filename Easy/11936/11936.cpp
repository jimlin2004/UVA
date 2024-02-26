#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
    int t;
    scanf("%d", &t);
    int sides[3];
    while (t--)
    {
        for (int i = 0; i < 3; ++i)
        {
            scanf("%d", &sides[i]);
        }
        sort(sides, sides + 3);
        puts((sides[0] + sides[1] > sides[2]) ? "OK" : "Wrong!!");
    }
    return 0;
}