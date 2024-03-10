#include <cstdio>
using namespace std;

/*
題意就是要求最大和所在的區段
要最長最早
Kadane
*/

int main()
{
    int t;
    scanf("%d", &t);
    int Case = 0;
    while (t--)
    {
        int n;
        scanf("%d", &n);
        int num;
        scanf("%d", &num);
        int start = 1;
        int end = 2;
        int currStart = 1;
        int currEnd = 2;
        int maxSum = num;
        int currSum = num;
        
        for (int i = 2; i < n; ++i)
        {
            scanf("%d", &num);
            if (currSum + num < num)
            {
                currSum = num;
                currStart = i;
                currEnd = i + 1;
            }
            else
            {
                currSum += num;
                ++currEnd;
            }

            if (currSum > maxSum || (currSum == maxSum && (currEnd - currStart > end - start)))
            {
                start = currStart;
                end = currEnd;
                maxSum = currSum;
            }
        }

        if (maxSum <= 0)
            printf("Route %d has no nice parts\n", ++Case);
        else
            printf("The nicest part of route %d is between stops %d and %d\n", ++Case, start, end);
    }
    return 0;
}

/*
3
3
-1
6
10
4
-5
4
-3
4
4
-4
4
-5
4
-2
-3
-4
*/