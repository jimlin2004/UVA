#include <bits/stdc++.h>
using namespace std;

char str[100];

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%s", str);

        int res = 0;
        int score = 0;

        int n = strlen(str);

        for (int i = 0; i < n; ++i)
        {
            if (str[i] == 'O')
            {
                ++score;
                res += score;
            }
            else
                score = 0;
        }

        printf("%d\n", res);
    }

    return 0;
}