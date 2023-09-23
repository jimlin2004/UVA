#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
    int N;
    while (scanf("%d", &N) != EOF && N)
    {
        int currentSum = 0;
        int maxSum = -1;
        int input;
        for (int i = 0; i < N; ++i)
        {
            scanf("%d", &input);
            if (currentSum + input < 0)
            {
                maxSum = max(maxSum, currentSum);
                currentSum = 0;
            }
            else
            {
                currentSum += input;
                maxSum = max(maxSum, currentSum);
            }
        }

        if (maxSum <= 0)
        {
            printf("Losing streak.\n");
        }
        else
        {
            printf("The maximum winning streak is %d.\n", maxSum);
        }
    }
}