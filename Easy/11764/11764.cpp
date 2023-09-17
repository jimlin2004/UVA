#include <iostream>
using namespace std;

int main()
{
    int T, n;
    int highJump, lowJump;
    int prev, curr;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        highJump = 0;
        lowJump = 0;
        scanf("%d", &n);
        scanf("%d", &prev);
        for (int i = 1; i < n; ++i)
        {
            scanf("%d", &curr);
            if (curr > prev)
                ++highJump;
            else if (curr < prev)
                ++lowJump;
            prev = curr;
        }
        printf("Case %d: %d %d\n", t, highJump, lowJump);
    }
}