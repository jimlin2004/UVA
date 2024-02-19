#include <cstdio>

int scores[1005];

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        int total = 0;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &scores[i]);
            total += scores[i];
        }
        double avg = (total * 1.0) / n;
        int count = 0;
        for (int i = 0; i < n; ++i)
        {
            if (scores[i] > avg)
                ++count;
        }
        printf("%.3lf%\n", ((count * 1.0) / n) * 100.0);
    }
    return 0;
}