#include <cstdio>
using namespace std;

int nums[55];

int bubbleSort(int n)
{
    int count = 0;
    bool swaped;
    for (int i = 0; i < n - 1; ++i)
    {
        swaped = false;
        for (int j = 0; j < n - 1; ++j)
        {
            if (nums[j] > nums[j + 1])
            {
                swaped = true;
                ++count;
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
        if (!swaped)
            break;
    }
    return count;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            scanf("%d", &nums[i]);
        printf("Optimal train swapping takes %d swaps.\n", bubbleSort(n));
    }
    return 0;
}