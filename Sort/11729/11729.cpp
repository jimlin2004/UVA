#include <iostream>
#include <algorithm>
using namespace std;
// B的總和每種配法皆相同，所以要盡量讓J重疊(由大牌到小)

struct Solder
{
    int B, J;
    bool operator <(const Solder& other)
    {
        return this->J > other.J;
    }
} solders[1005];

int main()
{
    int n, Case = 1;
    while (scanf("%d", &n) != EOF)
    {
        if (n == 0)
            break;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d", &solders[i].B, &solders[i].J);
        }
        sort(solders, solders + n);
        int ans = 0, time = 0;
        for (int i = 0; i < n; ++i)
        {
            time += solders[i].B;
            ans = max(ans, time + solders[i].J);
        }
        printf("Case %d: %d\n", Case++, ans);
    }
    return 0;
}