#include <cstdio>
#include <cstring>

int counter[10];

int main()
{
    int maxN;
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &maxN);
        memset(counter, 0, sizeof(counter));
        int temp;
        for (int i = 1; i <= maxN; ++i)
        {
            temp = i;
            while (temp > 0)
            {
                ++counter[temp % 10];
                temp /= 10;
            }
        }

        printf("%d", counter[0]);
        for (int i = 1; i < 10; ++i)
        {
            printf(" %d", counter[i]);
        }
        puts("");
    }
    return 0;
}