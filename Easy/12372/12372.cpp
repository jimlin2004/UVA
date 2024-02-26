#include <cstdio>

int main()
{
    int t;
    scanf("%d", &t);
    int Case = 0;
    while (t--)
    {
        int len;
        bool ok = true;
        for (int i = 0; i < 3; ++i)
        {
            scanf("%d", &len);
            if (len > 20)
                ok = false;
        }
        if (ok)
            printf("Case %d: good\n", ++Case);
        else
            printf("Case %d: bad\n", ++Case);
    }
    return 0;
}