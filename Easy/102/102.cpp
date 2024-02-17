#include <cstdio>

int B[3];
int G[3];
int C[3];

int count[6];

int main()
{
    const char ans[6][4] = {"BCG", "BGC", "CBG", "CGB", "GBC", "GCB"};
    while (scanf("%d", &B[0]) != EOF)
    {
        scanf("%d %d %d %d %d %d %d %d", &G[0], &C[0], 
            &B[1], &G[1], &C[1], 
            &B[2], &G[2], &C[2]);
        //BCG
        count[0] = B[1] + B[2] + G[0] + G[1] + C[0] + C[2];
        //BGC
        count[1] = B[1] + B[2] + G[0] + G[2] + C[0] + C[1];
        //CBG
        count[2] = B[0] + B[2] + G[0] + G[1] + C[1] + C[2];
        //CGB
        count[3] = B[0] + B[1] + G[0] + G[2] + C[1] + C[2];
        //GBC
        count[4] = B[0] + B[2] + G[1] + G[2] + C[0] + C[1];
        //GCB
        count[5] = B[0] + B[1] + G[1] + G[2] + C[0] + C[2];
        int minRes = 0x3f3f3f3f;
        int minStrIndex = -1;
        for (int i = 0; i < 6; ++i)
        {
            if (count[i] < minRes)
            {
                minRes = count[i];
                minStrIndex = i;
            }
        }
        printf("%s %d\n", ans[minStrIndex], minRes);
    }
    return 0;
}