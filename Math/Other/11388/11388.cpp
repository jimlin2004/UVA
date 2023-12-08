#include <iostream>

/*
    if (LCM 不是 GCD的倍數)
        return -1;
    else
        存在some解
    a要最小
    GCD就是滿足條件的最小值
*/

int main()
{
    int T;
    int G, L;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &G, &L);
        if (L % G != 0)
            printf("-1\n");
        else
            printf("%d %d\n", G, L);
    }
    return 0;
}