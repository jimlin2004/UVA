#include <cstdio>

//devices[n][0] -> n關著，[n][1] -> n開著
int devices[25][2];

int main()
{
    int n, m, c;
    int Case = 0;
    while (scanf("%d %d %d", &n, &m, &c) && n)
    {
        int maxP = -1;
        int curr = 0;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &devices[i][0]);
            devices[i][1] = 0;
        }
            
        int index;
        bool broken = false;
        for (int i = 1; i <= m; ++i)
        {
            scanf("%d", &index);
            devices[index][1] ^= 1;
            if (devices[index][1] == 1)
                curr += devices[index][0];
            else
                curr -= devices[index][0];
            if (curr > maxP)
                maxP = curr;
            if (curr > c)
                broken = true;
        }

        printf("Sequence %d\n", ++Case);

        if (broken)
            printf("Fuse was blown.\n");
        else
            printf("Fuse was not blown.\nMaximal power consumption was %d amperes.\n", maxP);
        puts("");
    }
    return 0;
}

/*
3 6 10
2
5
7
2
1
2
3
1
3
*/