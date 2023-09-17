#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max(a,b) (((a) > (b)) ? (a) : (b))

int main()
{
    int N1, N2;
    int T1[101];
    int T2[101];
    int lcs[101][101];
    int count = 1;
    while (scanf("%d %d", &N1, &N2))
    {
        if (N1 == 0 && N2 == 0)
            break;
        printf("Twin Towers #%d\n", count);
        T1[0] = 0;
        T2[0] = 0;
        lcs[0][0] = 0;
        for (int i = 1; i <= N1; i++)
        {
            lcs[i][0] = 0;
            scanf("%d", &T1[i]);
        }
        for (int j = 1; j <= N2; j++)
        {
            lcs[0][j] = 0;
            scanf("%d", &T2[j]);
        }
        for (int i = 1; i <= N1; i++)
            for (int j = 1; j <= N2; j++)
            {
                if (T1[i] == T2[j])
                    lcs[i][j] = lcs[i - 1][j - 1] + 1;
                else
                    lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
            }
        printf("Number of Tiles : %d\n\n", lcs[N1][N2]);
        count++;
    }
}