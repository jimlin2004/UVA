#include <cstdio>

int main()
{
    int mile, juice;
    int t;
    scanf("%d", &t);
    int Case = 0;
    while (t--)
    {
        mile = 0;
        juice = 0;
        int n;
        scanf("%d", &n);
        int d;
        while (n--)
        {
            scanf("%d", &d);
            //這題30、60卻是算下一個時段，所以右移1使下面算法成立
            ++d;
            mile += (d / 30) * 10;
            if (d % 30 != 0)
                mile += 10;
            juice += (d / 60) * 15;
            if (d % 60 != 0)
                juice += 15;
        }
        if (mile < juice)
            printf("Case %d: Mile %d\n", ++Case, mile);
        else if (mile > juice)
            printf("Case %d: Juice %d\n", ++Case, juice);
        else
            printf("Case %d: Mile Juice %d\n", ++Case, mile);
    }
    return 0;
}