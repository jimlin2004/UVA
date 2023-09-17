#include <iostream>
#include <algorithm>
using namespace std;

int nums[2000005];

int main()
{
    int n;
    while (scanf("%d", &n) != EOF && n != 0)
    {
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &nums[i]);
        }
        sort(nums, nums + n);
        for (int i = 0; i < n; ++i)
        {
            if (i != 0)
                putchar(' ');
            printf("%d", nums[i]);
        }
        puts("");
    }
    return 0;
}