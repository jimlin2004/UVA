#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int nums[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
vector<pair<int, int>> ans[100];

int main()
{
    const unsigned int maxBit = 1 << 10;
    int n;
    bool first = true;

    do
    {
        int a = 0;
        int b = 0;
        for (int i = 0; i < 5; ++i)
        {
            a *= 10;
            a += nums[i];
        }

        for (int i = 5; i < 10; ++i)
        {
            b *= 10;
            b += nums[i];
        }

        if (a > 1000 && b > 1000)
        {
            if (a % b == 0)
            {
                ans[a / b].push_back({a, b});
            }
        }
    } while (next_permutation(nums, nums + 10));

    while (scanf("%d", &n) && n)
    {
        if (first)
            first = false;
        else
            puts("");

        if (ans[n].empty())
        {
            printf("There are no solutions for %d.\n", n);
        }
        else
        {
            for (const pair<int, int>& p: ans[n])
            {
                printf("%05d / %05d = %d\n", p.first, p.second, n);
            }
        }
    }
    return 0;
}