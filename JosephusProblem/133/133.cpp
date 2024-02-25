#include <cstdio>
#include <cstring>

bool killed[25];

//雙向的JosephusProblem，直接模擬

int main()
{
    int n, k, m;
    while (scanf("%d %d %d", &n, &k, &m) != EOF && (n * k * m != 0))
    {
        int forward = -1;
        int backward = n;
        int killCount = 0;
        memset(killed, false, sizeof(killed));
        while (killCount < n)
        {
            for (int i = 0; i < k; ++i)
            {
                do
                {
                    forward = (forward + 1) % n;
                } while (killed[forward]);
            }

            for (int i = 0; i < m; ++i)
            {
                do
                {
                    backward = (backward - 1 + n) % n;
                } while (killed[backward]);
            }

            killed[forward] = true;
            killed[backward] = true;

            if (killCount > 0)
                printf(",");

            if (forward == backward)
            {
                printf("%3d", forward + 1);
                ++killCount;
            }
            else
            {
                printf("%3d%3d", forward + 1, backward + 1);
                killCount += 2;
            }
        }
        puts("");
    }
    return 0;
}